代码实现保存聊天图片
PC微信逆向：实现自动保存加密的聊天图片
https://www.52pojie.cn/thread-1031629-1-1.html
----------------------------


void HookSaveImages()
{
    DWORD dwBaseAddress = (DWORD)GetModuleHandle(TEXT("WeChatWin.dll"));
    
    //需要hook的地址
    SaveImageAddress = dwBaseAddress + SaveImages;

    //跳回的地址
    SaveImageAddressBackAddress = SaveImageAddress + 5;

    //组装跳转数据
    BYTE jmpCode[5] = { 0 };
    jmpCode[0] = 0xE9;

    //计算偏移
    *(DWORD*)& jmpCode[1] = (DWORD)FnSaveImages - SaveImageAddress - 5;

    // 保存以前的属性用于还原
    DWORD OldProtext = 0;

    // 因为要往代码段写入数据，又因为代码段是不可写的，所以需要修改属性
    VirtualProtect((LPVOID)SaveImageAddress, 5, PAGE_EXECUTE_READWRITE, &OldProtext);

    //写入自己的代码
    memcpy((void*)SaveImageAddress, jmpCode, 5);

    // 执行完了操作之后需要进行还原
    VirtualProtect((LPVOID)SaveImageAddress, 5, OldProtext, &OldProtext);
}

------------------

__declspec(naked) void FnSaveImages()
{
    __asm
    {
        mov ebx, dword ptr ss : [ebp - 0x4];
        mov ImageData, ebx;
        mov ImageDataLen, ecx;
        pushad;
        pushfd;
    }

    //调用接收消息的函数
    FnSaveImagesCore();

    //恢复现场
    __asm
    {
        popfd
        popad
        //跳回被HOOK指令的下一条指令
        jmp SaveImageAddressBackAddress;
    }
}

-------------------

void FnSaveImagesCore()
{
    //如果图片长度大于10KB则保存
    if (ImageDataLen >= 10240)
    {

        //获取临时文件夹目录
        char temppath[MAX_PATH] = { 0 };
        GetTempPathA(MAX_PATH, temppath);
        char imagedir[20] = { "WeChatRecordImages" };

        //拼接目录
        char WeChatExpressionsPath[MAX_PATH] = { 0 };
        sprintf_s(WeChatExpressionsPath, "%s%s\\", temppath, imagedir);
        //创建目录存放图片
        CreateDir(WeChatExpressionsPath);

        //保存图片
        CreateFileWithCurrentTime(WeChatExpressionsPath, (char*)".jpg", ImageData, ImageDataLen);
    }
}
