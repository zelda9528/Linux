#$(wildcard ./*.c)表示获取当前目录下所有以.c结尾的文件名
src=$(wildcard ./*.c)
#表示将src内容中的.c替换成.o存放在obj变量中
obj=$(patsubst %.c, %.o, $(src))
test:$(obj)
	gcc $^ -o $@
%.o:%.c
	gcc -c $< -o $@

#伪对象：声明一个对象，与外部文件无关，每次都要重新生成(不会因为当前文件是最新的而导致不需要重新生成)
.PHONY:clean
clean:
	rm -r $(obj) test
