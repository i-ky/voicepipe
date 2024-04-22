# voicepipe

[A simple communication device](https://en.wikipedia.org/wiki/Speaking_tube)
for use with
[development containers](https://containers.dev).

## summary

Development containers are great.
But there is an issue which can be seen in the following picture:
![dev container vs. production container depiction](https://containers.dev/img/dev-container-stages.png)
It's not to scale!
Stuff required to _run_ the application is only a fraction (both in numbers and in size) of the stuff required to _develop_ it.
All those compilers, SDKs, build tools, debuggers, productivity tools, etc.
when put into a _single container_ may at some point start to interfere with one another.
Tools that are useful, say, 1% of the time will still sit there increasing image build time and size.
Abundance of things means more frequent upgrades and hence more frequent image rebuilds.
Moreover, upgrading any one thing will require rebuilding half of the image
due to how [build cache](https://docs.docker.com/build/cache/) works.
This means that you are about to spend O(N<sup>2</sup>) time rebuilding your dev container
(where N is the number of things installed into it).

The solution is to split development environment into _multiple containers_,
each responsible for its own compiler, SDK, build tool, debugger, etc.
Each can be built and run independently.
All is needed is a voicepipe.
One container will shout commands into it.
On the other side a different container will run the command and send the results back.

## disclaimer

It has been developed and tested on Linux.
Whether it works on other systems is an open question.
Your feedback (both positive and negative) is highly appreciated!

## prerequisites

You will need `make` and C++ compiler.

## compile

Simply:
```bash
make
```
It should produce `voicepipe-client` and `voicepipe-server` executables in the project root directory.

## install

Copy `voicepipe-client` executable into the container where you want to shout commands into a voicepipe.
Create symlinks pointing to it named after the commands you want to offload into a different container.
Make sure those symlinks are in `PATH`.

Copy `voicepipe-server` executable into the containers that are responsible for running the commands.
Set it as container's [`ENTRYPOINT`](https://docs.docker.com/reference/dockerfile/#entrypoint).

## configure

## use

