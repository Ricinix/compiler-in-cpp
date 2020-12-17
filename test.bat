@echo off
:: 记录下当前路径，并切换到对应路径
pushd cmake-build-debug
:: 运行程序
design_1 -c ../data/test_1.st > ../data/test_1.log
:: 返回刚才的路径
popd