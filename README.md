# ImageScaler

This is a small utility that proportionally scales images.

# Usage

List options by executing `imagescaler --help`. Use either `-w` or `-h` to scale files
to the specified width or height.

## Scale image file to width of 1024 px

```
imagescaler -w 1024 image.png
```

## Scale image file to height of 1024 px

```
imagescaler -h 1024 image.png
```

## Scale image files to width of 1024 px and store to output directory

Previous commands saved scaled image files in-place. To save scaled files
to output directory, specify that directory as the last file:

```
mkdir out
imagescaler -w 1024 image1.png image2.jpg out
```

## Set default option

Rename `imagescaler` to `imagescaler -w 1024` to scale image files
to width of 1024 px. You can execute scaling by

```
imagescaler\ -w\ 1024 image1.png
```

You also enable execution by drag-and-drop through this.

# Requirements

* C++11 compiler
* Boost (with `program_options` and `filesystem`)
* ImageMagick

# License

[Apache 2.0](LICENSE)
