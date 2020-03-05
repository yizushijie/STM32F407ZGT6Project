#ifndef AES_CFG_H_
#define AES_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	//////////////////////////////////////////////////////////////////////////////////////
	#define MAX_LEN							(2*1024*1024)
	#define AES_KEY_SIZE					128
	#define AES_BLOCK_SIZE					16               // AES operates on 16 UINT8_Ts at a time
	#define AES_128_ROUNDS					10
	#define AES_192_ROUNDS					12
	#define AES_256_ROUNDS					14
	#define KE_ROTUINT32_T(x)					(((x) << 8) | ((x) >> 24))

	
	//===º¯Êý¶¨Òå
	void	aes_key_setup(const UINT8_T key[], UINT32_T w[], int keysize);
	void	aes_encrypt(const UINT8_T in[], UINT8_T out[], const UINT32_T key[], int keysize);
	void	aes_decrypt(const UINT8_T in[], UINT8_T out[], const UINT32_T key[], int keysize);
	int		aes_encrypt_cbc(const UINT8_T in[], size_t in_len, UINT8_T out[], const UINT32_T key[], int keysize, const UINT8_T iv[]);
	int		aes_decrypt_cbc(const UINT8_T in[], size_t in_len, UINT8_T out[], const UINT32_T key[], int keysize, const UINT8_T iv[]);
	int		aes_encrypt_cbc_mac(const UINT8_T in[], size_t in_len, UINT8_T out[], const UINT32_T key[], int keysize, const UINT8_T iv[]);
	void	increment_iv(UINT8_T iv[], int counter_size);
	void	aes_encrypt_ctr(const UINT8_T in[], size_t in_len, UINT8_T out[], const UINT32_T key[], int keysize, const UINT8_T iv[]);
	void	aes_decrypt_ctr(const UINT8_T in[], size_t in_len, UINT8_T out[], const UINT32_T key[], int keysize, const UINT8_T iv[]);
	int		aes_encrypt_ccm(const UINT8_T plaintext[], UINT32_T plaintext_len, const UINT8_T associated_data[], unsigned short associated_data_len, const UINT8_T nonce[], unsigned short nonce_len, UINT8_T ciphertext[], UINT32_T* ciphertext_len, UINT32_T mac_len, const UINT8_T key[], int keysize);
	int		aes_decrypt_ccm(const UINT8_T ciphertext[], UINT32_T ciphertext_len, const UINT8_T assoc[], unsigned short assoc_len, const UINT8_T nonce[], unsigned short nonce_len, UINT8_T plaintext[], UINT32_T* plaintext_len, UINT32_T mac_len, int* mac_auth, const UINT8_T key[], int keysize);
	unsigned char* encrypt(const unsigned char* in, int in_len, unsigned int* out_len,const unsigned char* key, const unsigned char* iv);
	unsigned char* decrypt(const unsigned char* in, int in_len, unsigned int* out_len,const unsigned char* key, const unsigned char* iv);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*AES_CFG_H_ */