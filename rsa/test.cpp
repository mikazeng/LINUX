#include <stdio.h>
#include <string>
#include <string.h>
#include <iostream>
#include <vector>
#include <openssl/rsa.h>
using namespace std;
int main()
{
	RSA * rsa =RSA_generate_key(1024,RSA_3,NULL,NULL);

	unsigned char plain[512]="我　爱　　　你　";
	unsigned char cipper[512]={0},newplain[512]={0};
	size_t outl=512,outl2;

	cout<<"明文:"<<plain<<endl;

	for(int i =0;i<strlen((char*)plain);i++)
	{
		printf("%0.2X ",plain[i]);
	}
	printf("\n");

	outl=RSA_public_encrypt(strlen((char*)plain),plain,cipper,rsa,RSA_PKCS1_OAEP_PADDING);

	cout<<"密文："<<cipper<<endl;
	cout<<"hex:";
	for(int i =0;i<outl;i++)
	{
		printf("%0.2X ",cipper[i]);
	}
	printf("\n");
	outl2=RSA_private_decrypt(outl,cipper,newplain,rsa,RSA_PKCS1_OAEP_PADDING);
	cout<<"解密后明文:"<<newplain<<endl;
	cout<<"hex:";
	for(int i =0;i<outl2;i++)
	{
		printf("%0.2X ",newplain[i]);
	}
	printf("\n");
	return 0;
}
