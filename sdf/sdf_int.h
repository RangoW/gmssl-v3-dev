/* 
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

#ifndef HEADER_SDF_METH_H
#define HEADER_SDF_METH_H


#include "sdf.h"


typedef int (*SDF_OpenDevice_FuncPtr)(
	void **phDeviceHandle);

typedef int (*SDF_CloseDevice_FuncPtr)(
	void *hDeviceHandle);

typedef int (*SDF_OpenSession_FuncPtr)(
	void *hDeviceHandle,
	void **phSessionHandle);

typedef int (*SDF_CloseSession_FuncPtr)(
	void *hSessionHandle);

typedef int (*SDF_GetDeviceInfo_FuncPtr)(
	void *hSessionHandle,
	DEVICEINFO *pstDeviceInfo);

typedef int (*SDF_GenerateRandom_FuncPtr)(
	void *hSessionHandle,
	unsigned int uiLength,
	unsigned char *pucRandom);

typedef int (*SDF_GetPrivateKeyAccessRight_FuncPtr)(
	void *hSessionHandle,
	unsigned int uiKeyIndex,
	unsigned char *pucPassword,
	unsigned int uiPwdLength);

typedef int (*SDF_ReleasePrivateKeyAccessRight_FuncPtr)(
	void *hSessionHandle,
	unsigned int uiKeyIndex);

typedef int (*SDF_ExportSignPublicKey_RSA_FuncPtr)(
	void *hSessionHandle,
	unsigned int uiKeyIndex,
	RSArefPublicKey *pucPublicKey);

typedef int (*SDF_ExportEncPublicKey_RSA_FuncPtr)(
	void *hSessionHandle,
	unsigned int uiKeyIndex,
	RSArefPublicKey *pucPublicKey);

typedef int (*SDF_GenerateKeyPair_RSA_FuncPtr)(
	void *hSessionHandle,
	unsigned int uiKeyBits,
	RSArefPublicKey *pucPublicKey,
	RSArefPrivateKey *pucPrivateKey);

typedef int (*SDF_GenerateKeyWithIPK_RSA_FuncPtr)(
	void *hSessionHandle,
	unsigned int uiIPKIndex,
	unsigned int uiKeyBits,
	unsigned char *pucKey,
	unsigned int *puiKeyLength,
	void **phKeyHandle);

typedef int (*SDF_GenerateKeyWithEPK_RSA_FuncPtr)(
	void *hSessionHandle,
	unsigned int uiKeyBits,
	RSArefPublicKey *pucPublicKey,
	unsigned char *pucKey,
	unsigned int *puiKeyLength,
	void **phKeyHandle);

typedef int (*SDF_ImportKeyWithISK_RSA_FuncPtr)(
	void *hSessionHandle,
	unsigned int uiISKIndex,
	unsigned char *pucKey,
	unsigned int uiKeyLength,
	void **phKeyHandle);

typedef int (*SDF_ExchangeDigitEnvelopeBaseOnRSA_FuncPtr)(
	void *hSessionHandle,
	unsigned int uiKeyIndex,
	RSArefPublicKey *pucPublicKey,
	unsigned char *pucDEInput,
	unsigned int uiDELength,
	unsigned char *pucDEOutput,
	unsigned int *puiDELength);

typedef int (*SDF_ExportSignPublicKey_ECC_FuncPtr)(
	void *hSessionHandle,
	unsigned int uiKeyIndex,
	ECCrefPublicKey *pucPublicKey);

typedef int (*SDF_ExportEncPublicKey_ECC_FuncPtr)(
	void *hSessionHandle,
	unsigned int uiKeyIndex,
	ECCrefPublicKey *pucPublicKey);

typedef int (*SDF_GenerateKeyPair_ECC_FuncPtr)(
	void *hSessionHandle,
	unsigned int uiAlgID,
	unsigned int  uiKeyBits,
	ECCrefPublicKey *pucPublicKey,
	ECCrefPrivateKey *pucPrivateKey);

typedef int (*SDF_GenerateKeyWithIPK_ECC_FuncPtr)(
	void *hSessionHandle,
	unsigned int uiIPKIndex,
	unsigned int uiKeyBits,
	ECCCipher *pucKey,
	void **phKeyHandle);

typedef int (*SDF_GenerateKeyWithEPK_ECC_FuncPtr)(
	void *hSessionHandle,
	unsigned int uiKeyBits,
	unsigned int uiAlgID,
	ECCrefPublicKey *pucPublicKey,
	ECCCipher *pucKey,
	void **phKeyHandle);

typedef int (*SDF_ImportKeyWithISK_ECC_FuncPtr)(
	void *hSessionHandle,
	unsigned int uiISKIndex,
	ECCCipher *pucKey,
	void **phKeyHandle);

typedef int (*SDF_GenerateAgreementDataWithECC_FuncPtr)(
	void *hSessionHandle,
	unsigned int uiISKIndex,
	unsigned int uiKeyBits,
	unsigned char *pucSponsorID,
	unsigned int uiSponsorIDLength,
	ECCrefPublicKey *pucSponsorPublicKey,
	ECCrefPublicKey *pucSponsorTmpPublicKey,
	void **phAgreementHandle);

typedef int (*SDF_GenerateKeyWithECC_FuncPtr)(
	void *hSessionHandle,
	unsigned char *pucResponseID,
	unsigned int uiResponseIDLength,
	ECCrefPublicKey *pucResponsePublicKey,
	ECCrefPublicKey *pucResponseTmpPublicKey,
	void *hAgreementHandle,
	void **phKeyHandle);

typedef int (*SDF_GenerateAgreementDataAndKeyWithECC_FuncPtr)(
	void *hSessionHandle,
	unsigned int uiISKIndex,
	unsigned int uiKeyBits,
	unsigned char *pucResponseID,
	unsigned int uiResponseIDLength,
	unsigned char *pucSponsorID,
	unsigned int uiSponsorIDLength,
	ECCrefPublicKey *pucSponsorPublicKey,
	ECCrefPublicKey *pucSponsorTmpPublicKey,
	ECCrefPublicKey *pucResponsePublicKey,
	ECCrefPublicKey *pucResponseTmpPublicKey,
	void **phKeyHandle);

typedef int (*SDF_ExchangeDigitEnvelopeBaseOnECC_FuncPtr)(
	void *hSessionHandle,
	unsigned int uiKeyIndex,
	unsigned int uiAlgID,
	ECCrefPublicKey *pucPublicKey,
	ECCCipher *pucEncDataIn,
	ECCCipher *pucEncDataOut);

typedef int (*SDF_GenerateKeyWithKEK_FuncPtr)(
	void *hSessionHandle,
	unsigned int uiKeyBits,
	unsigned int uiAlgID,
	unsigned int uiKEKIndex,
	unsigned char *pucKey,
	unsigned int *puiKeyLength,
	void **phKeyHandle);

typedef int (*SDF_ImportKeyWithKEK_FuncPtr)(
	void *hSessionHandle,
	unsigned int uiAlgID,
	unsigned int uiKEKIndex,
	unsigned char *pucKey,
	unsigned int uiKeyLength,
	void **phKeyHandle);

typedef int (*SDF_DestroyKey_FuncPtr)(
	void *hSessionHandle,
	void *hKeyHandle);

typedef int (*SDF_ExternalPublicKeyOperation_RSA_FuncPtr)(
	void *hSessionHandle,
	RSArefPublicKey *pucPublicKey,
	unsigned char *pucDataInput,
	unsigned int uiInputLength,
	unsigned char *pucDataOutput,
	unsigned int *puiOutputLength);

typedef int (*SDF_InternalPublicKeyOperation_RSA_FuncPtr)(
	void *hSessionHandle,
	unsigned int uiKeyIndex,
	unsigned char *pucDataInput,
	unsigned int uiInputLength,
	unsigned char *pucDataOutput,
	unsigned int *puiOutputLength);

typedef int (*SDF_InternalPrivateKeyOperation_RSA_FuncPtr)(
	void *hSessionHandle,
	unsigned int uiKeyIndex,
	unsigned char *pucDataInput,
	unsigned int uiInputLength,
	unsigned char *pucDataOutput,
	unsigned int *puiOutputLength);

typedef int (*SDF_ExternalVerify_ECC_FuncPtr)(
	void *hSessionHandle,
	unsigned int uiAlgID,
	ECCrefPublicKey *pucPublicKey,
	unsigned char *pucDataInput,
	unsigned int uiInputLength,
	ECCSignature *pucSignature);

typedef int (*SDF_InternalSign_ECC_FuncPtr)(
	void *hSessionHandle,
	unsigned int uiISKIndex,
	unsigned char *pucData,
	unsigned int uiDataLength,
	ECCSignature *pucSignature);

typedef int (*SDF_InternalVerify_ECC_FuncPtr)(
	void *hSessionHandle,
	unsigned int uiIPKIndex,
	unsigned char *pucData,
	unsigned int uiDataLength,
	ECCSignature *pucSignature);

typedef int (*SDF_ExternalEncrypt_ECC_FuncPtr)(
	void *hSessionHandle,
	unsigned int uiAlgID,
	ECCrefPublicKey *pucPublicKey,
	unsigned char *pucData,
	unsigned int uiDataLength,
	ECCCipher *pucEncData);

typedef int (*SDF_ExternalDecrypt_ECC_FuncPtr)(
	void *hSessionHandle,
	unsigned int uiAlgID,
	ECCrefPrivateKey *pucPrivateKey,
	ECCCipher *pucEncData,
	unsigned char *pucData,
	unsigned int *puiDataLength);

typedef int (*SDF_InternalEncrypt_ECC_FuncPtr)(
	void *hSessionHandle,
	unsigned int uiIPKIndex,
	unsigned int uiAlgID,
	unsigned char *pucData,
	unsigned int uiDataLength,
	ECCCipher *pucEncData);

typedef int (*SDF_InternalDecrypt_ECC_FuncPtr)(
	void *hSessionHandle,
	unsigned int uiISKIndex,
	unsigned int uiAlgID,
	ECCCipher *pucEncData,
	unsigned char *pucData,
	unsigned int *puiDataLength);

typedef int (*SDF_Encrypt_FuncPtr)(
	void *hSessionHandle,
	void *hKeyHandle,
	unsigned int uiAlgID,
	unsigned char *pucIV,
	unsigned char *pucData,
	unsigned int uiDataLength,
	unsigned char *pucEncData,
	unsigned int *puiEncDataLength);

typedef int (*SDF_Decrypt_FuncPtr)(
	void *hSessionHandle,
	void *hKeyHandle,
	unsigned int uiAlgID,
	unsigned char *pucIV,
	unsigned char *pucEncData,
	unsigned int uiEncDataLength,
	unsigned char *pucData,
	unsigned int *puiDataLength);

typedef int (*SDF_CalculateMAC_FuncPtr)(
	void *hSessionHandle,
	void *hKeyHandle,
	unsigned int uiAlgID,
	unsigned char *pucIV,
	unsigned char *pucData,
	unsigned int uiDataLength,
	unsigned char *pucMAC,
	unsigned int *puiMACLength);

typedef int (*SDF_HashInit_FuncPtr)(
	void *hSessionHandle,
	unsigned int uiAlgID,
	ECCrefPublicKey *pucPublicKey,
	unsigned char *pucID,
	unsigned int uiIDLength);

typedef int (*SDF_HashUpdate_FuncPtr)(
	void *hSessionHandle,
	unsigned char *pucData,
	unsigned int uiDataLength);

typedef int (*SDF_HashFinal_FuncPtr)(void *hSessionHandle,
	unsigned char *pucHash,
	unsigned int *puiHashLength);

typedef int (*SDF_CreateObject_FuncPtr)(
	void *hSessionHandle,
	unsigned char *pucFileName,
	unsigned int uiNameLen,
	unsigned int uiFileSize);

typedef int (*SDF_ReadObject_FuncPtr)(
	void *hSessionHandle,
	unsigned char *pucFileName,
	unsigned int uiNameLen,
	unsigned int uiOffset,
	unsigned int *puiReadLength,
	unsigned char *pucBuffer);

typedef int (*SDF_WriteObject_FuncPtr)(
	void *hSessionHandle,
	unsigned char *pucFileName,
	unsigned int uiNameLen,
	unsigned int uiOffset,
	unsigned int uiWriteLength,
	unsigned char *pucBuffer);

typedef int (*SDF_DeleteObject_FuncPtr)(
	void *hSessionHandle,
	unsigned char *pucFileName,
	unsigned int uiNameLen);

typedef struct sdf_method_st {
	char *name;
	void *dso;
	SDF_OpenDevice_FuncPtr OpenDevice;
	SDF_CloseDevice_FuncPtr CloseDevice;
	SDF_OpenSession_FuncPtr OpenSession;
	SDF_CloseSession_FuncPtr CloseSession;
	SDF_GetDeviceInfo_FuncPtr GetDeviceInfo;
	SDF_GenerateRandom_FuncPtr GenerateRandom;
	SDF_GetPrivateKeyAccessRight_FuncPtr GetPrivateKeyAccessRight;
	SDF_ReleasePrivateKeyAccessRight_FuncPtr ReleasePrivateKeyAccessRight;
	SDF_ExportSignPublicKey_RSA_FuncPtr ExportSignPublicKey_RSA;
	SDF_ExportEncPublicKey_RSA_FuncPtr ExportEncPublicKey_RSA;
	SDF_GenerateKeyPair_RSA_FuncPtr GenerateKeyPair_RSA;
	SDF_GenerateKeyWithIPK_RSA_FuncPtr GenerateKeyWithIPK_RSA;
	SDF_GenerateKeyWithEPK_RSA_FuncPtr GenerateKeyWithEPK_RSA;
	SDF_ImportKeyWithISK_RSA_FuncPtr ImportKeyWithISK_RSA;
	SDF_ExchangeDigitEnvelopeBaseOnRSA_FuncPtr ExchangeDigitEnvelopeBaseOnRSA;
	SDF_ExportSignPublicKey_ECC_FuncPtr ExportSignPublicKey_ECC;
	SDF_ExportEncPublicKey_ECC_FuncPtr ExportEncPublicKey_ECC;
	SDF_GenerateKeyPair_ECC_FuncPtr GenerateKeyPair_ECC;
	SDF_GenerateKeyWithIPK_ECC_FuncPtr GenerateKeyWithIPK_ECC;
	SDF_GenerateKeyWithEPK_ECC_FuncPtr GenerateKeyWithEPK_ECC;
	SDF_ImportKeyWithISK_ECC_FuncPtr ImportKeyWithISK_ECC;
	SDF_GenerateAgreementDataWithECC_FuncPtr GenerateAgreementDataWithECC;
	SDF_GenerateKeyWithECC_FuncPtr GenerateKeyWithECC;
	SDF_GenerateAgreementDataAndKeyWithECC_FuncPtr GenerateAgreementDataAndKeyWithECC;
	SDF_ExchangeDigitEnvelopeBaseOnECC_FuncPtr ExchangeDigitEnvelopeBaseOnECC;
	SDF_GenerateKeyWithKEK_FuncPtr GenerateKeyWithKEK;
	SDF_ImportKeyWithKEK_FuncPtr ImportKeyWithKEK;
	SDF_DestroyKey_FuncPtr DestroyKey;
	SDF_ExternalPublicKeyOperation_RSA_FuncPtr ExternalPublicKeyOperation_RSA;
	SDF_InternalPublicKeyOperation_RSA_FuncPtr InternalPublicKeyOperation_RSA;
	SDF_InternalPrivateKeyOperation_RSA_FuncPtr InternalPrivateKeyOperation_RSA;
	SDF_ExternalVerify_ECC_FuncPtr ExternalVerify_ECC;
	SDF_InternalSign_ECC_FuncPtr InternalSign_ECC;
	SDF_InternalVerify_ECC_FuncPtr InternalVerify_ECC;
	SDF_ExternalEncrypt_ECC_FuncPtr ExternalEncrypt_ECC;
	SDF_ExternalDecrypt_ECC_FuncPtr ExternalDecrypt_ECC;
	SDF_InternalEncrypt_ECC_FuncPtr InternalEncrypt_ECC;
	SDF_InternalDecrypt_ECC_FuncPtr InternalDecrypt_ECC;
	SDF_Encrypt_FuncPtr Encrypt;
	SDF_Decrypt_FuncPtr Decrypt;
	SDF_CalculateMAC_FuncPtr CalculateMAC;
	SDF_HashInit_FuncPtr HashInit;
	SDF_HashUpdate_FuncPtr HashUpdate;
	SDF_HashFinal_FuncPtr HashFinal;
	SDF_CreateObject_FuncPtr CreateObject;
	SDF_ReadObject_FuncPtr ReadObject;
	SDF_WriteObject_FuncPtr WriteObject;
	SDF_DeleteObject_FuncPtr DeleteObject;
} SDF_METHOD;

SDF_METHOD *SDF_METHOD_load_library(const char *so_path);
void SDF_METHOD_free(SDF_METHOD *meth);


typedef struct sdf_vendor_st {
	char *name;
	unsigned int (*cipher_vendor2std)(unsigned int vendor_id);
	unsigned int (*cipher_std2vendor)(unsigned int std_id);
	unsigned int (*cipher_cap)(unsigned int vendor_cap);
	unsigned int (*digest_vendor2std)(unsigned int vendor_id);
	unsigned int (*digest_std2vendor)(unsigned int std_id);
	unsigned int (*digest_cap)(unsigned int vendor_cap);
	unsigned int (*pkey_vendor2std)(unsigned int vendor_id);
	unsigned int (*pkey_std2vendor)(unsigned int std_id);
	unsigned int (*pkey_cap)(unsigned int vendor_cap);
	int (*encode_ecccipher)(const ECCCipher *a, void *buf);
	int (*decode_ecccipher)(ECCCipher *a, const void *buf);
	unsigned long (*get_error_reason)(int err);
} SDF_VENDOR;


#endif
