glummy-glooma
===============

`glummy-glooma` is a sample C++ project to demonstrate using the conan package manager to import
OpenCV & FFmpeg as dependencies. While conan makes life easier in a lot of ways, there are some 
gotchas to working with these two particular libraries, particularly when using the OpenCV API for
video I/O (more below).

## Add bincrafters repo

The FFmpeg conan package is available in the [bincrafters](https://bintray.com/bincrafters/public-conan) 
repository, available through JFrog Bintray. If you haven't already configured conan to use 
bincrafters as a remote repo, run: 
```
$ conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
```

## Building

Now we are ready to build. Note that the first time building glummy-glooma, you will need to tell
`conan install` to build the FFmpeg and OpenCV packages from source. This is because the binary 
package for OpenCV on conan-center is not built with FFmpeg support, so it's effectively neutered 
for video I/O.

```
$ mkdir build && cd build
$ conan install .. --build ffmpeg --build opencv
$ cmake ..
$ cmake --build . --config Release
```

After building the first time, the FFmpeg and OpenCV binaries will be in your local conan cache, so 
you can leave off the `--build ffmpeg` and `--build opencv` arguments and building should be fast.

## Running

The application reads a video file, specified as a command-line argument:
```
$ bin/glummy-glooma <video_file>
```

If all goes well, it prints OpenCV build info, then the dimensions of the first video frame to 
standard output. It outputs the first frame of the video to the file `/bin/first_frame.png` just 
to prove reading was successful.

## Note on FFmpeg

At least on my system (Ubuntu 19.10), I had to set the following FFmpeg options in conanfile.txt 
in order to avoid link errors. Other combinations are of course possible, and may in fact be 
required on a different platform, YMMV.
```
ffmpeg:shared=True
ffmpeg:vaapi=False
ffmpeg:x264=False
ffmpeg:x265=False
```

Because these options are non-default, the pre-built binaries on bincrafters are not suitable, hence
the need for `--build ffmpeg` as part of the conan install step. It seems the C++ world is still a 
ways off from the ease of dependency management afforded by Maven/Gradle in Java land, but conan is
at least a step in the right direction.

