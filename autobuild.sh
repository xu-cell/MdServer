
#set -x 显示脚本执行过程，并显示脚本对变量的处理结果。如果，某一个脚本使用了大量的变量，而我们希望能看到这些变量的传递，使用是否正确，那么，set -x 将是你很好的选择。（快速定位问题，尤其是变量所产生的问题）
set -x

BUILD_TYPE=${BUILD_TYPE:-Debug}

rm -rf `pwd`/build/*

cd `pwd`/build &&
         cmake \
            -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
            .. \
        && make $*