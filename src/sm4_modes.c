﻿/* 
 *   Copyright 2014-2021 The GmSSL Project Authors. All Rights Reserved.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

#include <gmssl/sm4.h>
#include <gmssl/error.h>
#include <gmssl/gcm.h>
#include "mem.h"

void sm4_cbc_encrypt(const SM4_KEY *key, const uint8_t iv[16],
	const uint8_t *in, size_t nblocks, uint8_t *out)
{
	while (nblocks--) {
		gmssl_memxor(out, in, iv, 16);
		sm4_encrypt(key, out, out);
		iv = out;
		in += 16;
		out += 16;
	}
}

void sm4_cbc_decrypt(const SM4_KEY *key, const uint8_t iv[16],
	const uint8_t *in, size_t nblocks, uint8_t *out)
{
	while (nblocks--) {
		sm4_encrypt(key, in, out);
		memxor(out, iv, 16);
		iv = in;
		in += 16;
		out += 16;
	}
}

int sm4_cbc_padding_encrypt(const SM4_KEY *key, const uint8_t iv[16],
	const uint8_t *in, size_t inlen,
	uint8_t *out, size_t *outlen)
{
	uint8_t block[16];
	size_t rem = inlen % 16;
	int padding = 16 - inlen % 16;

	if (in) {
		memcpy(block, in + inlen - rem, rem);
	}
	memset(block + rem, padding, padding);
	if (inlen/16) {
		sm4_cbc_encrypt(key, iv, in, inlen/16, out);
		out += inlen - rem;
		iv = out - 16;
	}
	sm4_cbc_encrypt(key, iv, block, 1, out);
	*outlen = inlen - rem + 16;
	return 1;
}

int sm4_cbc_padding_decrypt(const SM4_KEY *key, const uint8_t iv[16],
	const uint8_t *in, size_t inlen,
	uint8_t *out, size_t *outlen)
{
	uint8_t block[16];
	size_t len = sizeof(block);
	int padding;

	if (inlen == 0) {
		error_puts("warning: input lenght = 0");
		return 0;
	}
	if (inlen%16 != 0 || inlen < 16) {
		error_puts("invalid cbc ciphertext length");
		return -1;
	}
	if (inlen > 16) {
		sm4_cbc_decrypt(key, iv, in, inlen/16 - 1, out);
		iv = in + inlen - 32;
	}
	sm4_cbc_decrypt(key, iv, in + inlen - 16, 1, block);
	padding = block[15];
	if (padding < 1 || padding > 16) {
		error_print();
		return -1;
	}
	len -= padding;
	memcpy(out + inlen - 16, block, len);
	*outlen = inlen - padding;
	return 1;
}

static void ctr_incr(uint8_t a[16])
{
	int i;
	for (i = 15; i > 0; i--) {
		a[i]++;
		if (a[i]) break;
	}
}

void sm4_ctr_encrypt(const SM4_KEY *key, uint8_t ctr[16], const uint8_t *in, size_t inlen, uint8_t *out)
{
	uint8_t block[16];
	size_t len;

	while (inlen) {
		len = inlen < 16 ? inlen : 16;
		sm4_encrypt(key, ctr, block);
		gmssl_memxor(out, in, block, len);
		ctr_incr(ctr);
		in += len;
		out += len;
		inlen -= len;
	}
}

int sm4_gcm_encrypt(const SM4_KEY *key, const uint8_t *iv, size_t ivlen,
	const uint8_t *aad, size_t aadlen, const uint8_t *in, size_t inlen,
	uint8_t *out, const size_t taglen, uint8_t *tag)
{
	const uint8_t *pin = in;
	uint8_t *pout = out;
	size_t left = inlen;
	uint8_t H[16] = {0};
	uint8_t Y[16];
	uint8_t T[16];

	sm4_encrypt(key, H, H);

	if (ivlen == 12) {
		memcpy(Y, iv, 12);
		Y[12] = Y[13] = Y[14] = 0;
		Y[15] = 1;
	} else {
		ghash(H, NULL, 0, iv, ivlen, Y);
	}

	sm4_encrypt(key, Y, T);

	while (left) {
		uint8_t block[16];
		size_t len = left < 16 ? left : 16;
		ctr_incr(Y);
		sm4_encrypt(key, Y, block);
		gmssl_memxor(pout, pin, block, len);
		pin += len;
		pout += len;
		left -= len;
	}

	ghash(H, aad, aadlen, out, inlen, H);
	gmssl_memxor(tag, T, H, taglen);
	return 1;
}

int sm4_gcm_decrypt(const SM4_KEY *key, const uint8_t *iv, size_t ivlen,
	const uint8_t *aad, size_t aadlen, const uint8_t *in, size_t inlen,
	const uint8_t *tag, size_t taglen, uint8_t *out)
{
	const uint8_t *pin = in;
	uint8_t *pout = out;
	size_t left = inlen;
	uint8_t H[16] = {0};
	uint8_t Y[16];
	uint8_t T[16];

	sm4_encrypt(key, H, H);

	if (ivlen == 12) {
		memcpy(Y, iv, 12);
		Y[12] = Y[13] = Y[14] = 0;
		Y[15] = 1;
	} else {
		ghash(H, NULL, 0, iv, ivlen, Y);
	}

	ghash(H, aad, aadlen, in, inlen, H);
	sm4_encrypt(key, Y, T);
	gmssl_memxor(T, T, H, taglen);
	if (memcmp(T, tag, taglen) != 0) {
		error_print();
		return -1;
	}

	while (left) {
		uint8_t block[16];
		size_t len = left < 16 ? left : 16;
		ctr_incr(Y);
		sm4_encrypt(key, Y, block);
		gmssl_memxor(pout, pin, block, len);
		pin += len;
		pout += len;
		left -= len;
	}
	return 1;
}
