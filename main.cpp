#include <iostream>
#include <string>
#include <random>

#include "openssl/evp.h"

std::string md5(const std::string& code)
{
    EVP_MD_CTX*   context = EVP_MD_CTX_new();
    const EVP_MD* md = EVP_md5();
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int  md_len;
    std::string   output;

    EVP_DigestInit_ex2(context, md, nullptr);
    EVP_DigestUpdate(context, code.c_str(), code.length());
    EVP_DigestFinal_ex(context, md_value, &md_len);
    EVP_MD_CTX_free(context);

    output.resize(md_len * 2);
    for (unsigned int i = 0 ; i < md_len ; ++i)
        std::sprintf(&output[i * 2], "%02x", md_value[i]);
    return output;
}

std::string FindMd5(const std::string& hash)
{
    std::string code(6, ' ');

    int sum1_6 = 222, sum3_4 = 212, sum2_5 = 209;

    for (int i=sum1_6-127; i<128; i++)
    {
        code[0] = i;
        code[5] = sum1_6 - i;

        for (int j=sum3_4-127; j<128; j++)
        {
            code[2] = j;
            code[3] = sum3_4 - j;

            for (int k=sum2_5-127; k<128; k++)
            {
                code[1] = k;
                code[4] = sum2_5 - k;

                if (md5(code) == hash)
                    return code;
            }
        }
    }
}

std::string GenerateCode()
{
    std::string code(6, ' ');
    int sum1_6 = 222, sum3_4 = 212, sum2_5 = 209;

    std::random_device rd;
    std::mt19937 e(rd());
    int c1 = std::uniform_int_distribution(sum1_6-127, 127)(e);
    int c2 = std::uniform_int_distribution(sum3_4-127, 127)(e);
    int c3 = std::uniform_int_distribution(sum2_5-127, 127)(e);

    code[0] = c1;
    code[1] = c2;
    code[2] = c3;
    code[3] = sum3_4 - c3;
    code[4] = sum2_5 - c2;
    code[5] = sum1_6 - c1;

    return code;
}

int main() {
    std::cout << "Generated code: " << GenerateCode() << std::endl;
    std::cout << "Code with specific md5 hash: " << FindMd5("96c4dda0c4a0b34262b1d91d47056f9e") << std::endl;
}
