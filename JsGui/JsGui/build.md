# ����webui
## ׼��
�޸� Makefile.nmake

��Ҫ�������⼸�У���release����뵽releaseĿ¼��ȥ
```
release:
	@- mkdir dist\release >nul 2>&1
	@- cd $(MAKEDIR)/dist/release
```

## ����
�� cmd

ִ�д�������
```
C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat
```
��CMD��ִ������
```
nmake -f Makefile debug
nmake -f Makefile
```