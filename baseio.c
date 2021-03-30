#include<stdio.h>
#include<string.h>

int main()
{
  //fopen(文件名,打开方式)
    FILE*fp=fopen("io.txt","wb+");
    if(fp==NULL)
    {
      perror("fopen error:");
      return -1;
    }
  //fwrite（数据，块大小，块个数，句柄）
    char *ptr="年薪100w!(doge)";
    int ret=fwrite(ptr,strlen(ptr),1,fp);
    if(ret==0)
    {
      perror("fwrite error:");
      return -1;
    }
  //fseek(句柄,偏移量,偏移相对起始位置)
   fseek(fp,0,SEEK_SET);

    char buf[1024]={0};
    ret=fread(buf,100,1,fp);
    if(ret==0)
    {
      if(feof(fp))
      {
        printf("读取到文件末尾\n");
      }
      if(ferror(fp))
      {
        perror("fread error:");
      }
    }
    printf("%d--%s\n",ret,buf);

    fclose(fp);


  return 0;
}
