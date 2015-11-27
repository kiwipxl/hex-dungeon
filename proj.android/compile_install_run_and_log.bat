call cocos run -p android
call "D:\android\apache-ant-1.9.6\bin\ant" clean debug -f D:\Development\C++\HexDungeon\proj.android\build.xml -Dsdk.dir="D:\android\android-sdk"
adb install -r "D:\Development\C++\HexDungeon\proj.android\bin\HexDungeon-debug.apk"
call run_and_log.bat