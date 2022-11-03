## Heat equation simulation

A quick project getting into gnuplot and such, making a simulation of the heat
equation.

![](https://github.com/JakobSachs/heatEquationC/blob/master/example.png?raw=true)


Usage:

```
make
./main
gnuplot plot.gpl
```

This renders the animation as a png-Sequence in `anim`. You can render this as
a video-file using _ffmpeg_ for example:

```
ffmpeg -i ani/data_%03d.dat.png output.avi
```


