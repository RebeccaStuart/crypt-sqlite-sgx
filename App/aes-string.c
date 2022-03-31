#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aes.h"
#include "aes-string.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION

#define STB_IMAGE_IMPLEMENTATION


//uint8_t key[4] = {0xef,0x45,0x3f,0xa6};

int offsetmult = 11;
int keylength = 16;

void phex(uint8_t* str)
{
    unsigned char i;
    for(i = 0; i < 16; ++i)
        printf("%.2x", str[i]);
    //printf("\n");
}

void phex_to_string(uint8_t* str, char* out)
{
    unsigned char i;
    char fullstring[65];
    for(i = 0; i < 16; ++i){
        char temp[4] = "";
        snprintf(temp,4,"%.2x", str[i]);
        if (i==0){
            strncpy(fullstring,temp,4);
        }
        else{
            strncat(fullstring,temp,4);
        } // this fixes the weird extra character issue
    }
    strncpy(out,fullstring,sizeof(fullstring));
}



void encrypt_str(uint8_t* str, uint8_t* out, int iter, uint8_t* key){
    uint8_t i;
    for (i = (uint8_t) 0; i <= (uint8_t) iter; ++i){
        AES128_ECB_encrypt(str + (i*16),key,out + (i*16));
    }
}

void decrypt_str(uint8_t* str, uint8_t* out, int iter, uint8_t* key){
    uint8_t i;
    for (i = (uint8_t) 0; i <= (uint8_t) iter; ++i){
        AES128_ECB_decrypt(str + (i*16),key,out + (i*16)); 
    }
}

int find_iterations(uint8_t* str){
    int iter;
    if (strlen(str) > 16){
        iter = (strlen(str)+16 -1) /16 ;
    }
    else{
        iter = 1;
    }
    return iter;
}

int hex_to_int(char c){
    if(c >=97) c=c-32;
    int first = c / 16 - 3;
    int second = c % 16;
    int result = first*10 + second;
    if(result > 9) result--;
    return result;
}

int hex_to_ascii(char c, char d){
        int high = hex_to_int(c) * 16;
        int low = hex_to_int(d);
        return high+low;
}

void convert_hex_str_to_asc(char* str, char* done){
	int i;
	int u = 0;
	char buf = 0;
	for (i=0;i<strlen(str);i++){
		if(i % 2 != 0){
            done[u] = hex_to_ascii(buf, str[i]);
            //printf("%s\n", done);
            u++;
        }else{
            buf = str[i];
        }
	}
}


char* encry(char* enc){
	uint8_t key[4] = {0xef,0x45,0x3f,0xa6};
	int iter = find_iterations(enc);
	uint8_t* dec = (uint8_t*)calloc(1,2*strlen(enc)); 
	encrypt_str(enc,dec, iter, key);
    
	return dec;
}
char* decry(char* dec){
	uint8_t key[4] = {0xef,0x45,0x3f,0xa6};
	int iter = find_iterations(dec);
	uint8_t* enc = (uint8_t*)calloc(1,2*strlen(dec));
	decrypt_str(dec,enc,iter, key);
	return enc;
}
int testall(){
char enc[]="jdsiojsdfojsdiof";
test(enc);
printf("-------------------------------------------------\n");
printf("-------------------------------------------------\n");
printf("-------------------------------------------------\n");
printf("encrypted enc,returns: %s\n",encry(enc));
printf("-------------------------------------------------\n");
printf("encrypted enc,returns: %s\n",decry(encry(enc)));
return 0;
}
int test(char*  enc){
	uint8_t key[4] = {0xef,0x45,0x3f,0xa6};
	//char enc[]="dsjfiosdjfoi";
	printf("initial string\n%s\n",enc);	
uint8_t* ascc = (uint8_t*)calloc(1,64);
convert_hex_str_to_asc(enc, ascc);
printf("-------------------------------------------------\n");
printf("initial string ascformat:\n%s\n",ascc);
	
	int iter = find_iterations(enc);
	uint8_t* dec = (uint8_t*)calloc(1,64); 
	encrypt_str(enc,dec, iter, key);
printf("-------------------------------------------------\n");

printf("encrypted string:\n%s\n",dec);

	uint8_t* asc = (uint8_t*)calloc(1,64);
	convert_hex_str_to_asc(dec, asc);
printf("-------------------------------------------------\n");

printf("encrypted string ascformat:\n%s\n",asc);
	iter = find_iterations(dec);
	uint8_t* decc = (uint8_t*)calloc(1,64);
	decrypt_str(dec,decc,iter, key);
printf("-------------------------------------------------\n");
printf("decrypted string:\n%s\n",decc);
	return 0;
}


void encrypp(uint8_t* str, uint8_t* enc,uint8_t* key){

    int iter = find_iterations(str);
    encrypt_str(str,enc, iter, key);

}

void decrypp(uint8_t* str, uint8_t* dec,uint8_t* key){

    int iter = find_iterations(str);
    
    decrypt_str(str,dec, iter, key);
    //phex_to_string(encc,str);

}

