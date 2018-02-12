/************************************************************************
 * RSA加密解密函数
 *
 * file: test_rsa_encdec.c
 * gcc -Wall -O2 -o test_rsa_encdec test_rsa_encdec.c -lcrypto -lssl
 *
 * author: tonglulin@gmail.com by www.qmailer.net
 * new author : 曾润良
 ************************************************************************/
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<openssl/rsa.h>
#include<openssl/pem.h>
#include<openssl/err.h>
#define BUFFSIZE 4096
using namespace std;
//加密类
class my_rsa_encrypt{
	public:
		char *str;//src
		char *en;//en 
	public:
		 my_rsa_encrypt(char *src):str(src),en(NULL)
	{
		RSA *rsa = NULL;
		FILE *fp = NULL;
		int len = 0;
		int rsa_len = 0;

		if ((fp = fopen("pubkey.pem", "r")) == NULL) {
			cout<<"pubkey open failed"<<endl;
			return ;
		}

		/* 读取公钥PEM，另一种PUBKEY格式PEM使用PEM_read_RSA_PUBKEY函数*/

		if ((rsa = PEM_read_RSAPublicKey(fp, NULL, NULL, NULL)) == NULL) {
			cout<<"pem read error"<<endl;
			return ;
		}

		RSA_print_fp(stdout, rsa, 0);

		len = strlen(str);
		rsa_len = RSA_size(rsa);

		en = (char *)malloc(rsa_len + 1);
		memset(en, 0, rsa_len + 1);

		if (RSA_public_encrypt(rsa_len, (unsigned char *)str, (unsigned char*)en, rsa, RSA_NO_PADDING) < 0) 
		{
			cout<<"rsa public encrypt"<<endl;
			return;
		}

		RSA_free(rsa);
		fclose(fp);
	}
		~my_rsa_encrypt()
		{
			if(en != NULL){
				free(en);
				en = NULL;
			}
		}
};

//解密类
class my_rsa_decrypt{
	public:
		char *de;//解密后
		char *str;//加密后的
		 my_rsa_decrypt(char *en):str(en),de(NULL)
	{
		RSA *rsa = NULL;
		FILE *fp = NULL;
		int rsa_len = 0;

		if ((fp = fopen("prikey.pem", "r")) == NULL) {
			cout<<"prikey open failed"<<endl;
			return ;
		}

		if ((rsa = PEM_read_RSAPrivateKey(fp, NULL, NULL, NULL)) == NULL) {
			cout<<"pem read"<<endl;
			return ;
		}

		RSA_print_fp(stdout, rsa, 0);

		rsa_len = RSA_size(rsa);
		de = (char *)malloc(rsa_len + 1);
		memset(de, 0, rsa_len + 1);

		if (RSA_private_decrypt(rsa_len, (unsigned char *)str, (unsigned char*)de, rsa, RSA_NO_PADDING) < 0) {
			cout<<"rsa private"<<endl;
			return ;
		}

		RSA_free(rsa);
		fclose(fp);
	}
		~my_rsa_decrypt()
		{
			if(de != NULL){
				free(de);
				de = NULL;
			}
		}
};
int main(int argc, char *argv[])
{
	char *src = "hello, world!";

	printf("src is: %s\n", src);

	my_rsa_encrypt *p =new my_rsa_encrypt(src);
	printf("enc is: %s\n", p->en);

	my_rsa_decrypt *q = new my_rsa_decrypt(p->en);
	printf("dec is: %s\n", q->de);

	return 0;
}
