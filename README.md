# WhiteboardCleaner

A small utility that implements whiteboard cleaning algorithm from the gist https://gist.github.com/lelandbatey/8677901.

# Usage

List options by executing `whiteboardcleaner --help`. There are not many.

## Clean whiteboard image

```
whiteboardcleaner image.png
```

You also can use this utility by drag-and-dropping the images onto the executable.

## Clean whiteboard images and store them to output directory

Previous command saved cleaned image files in-place. To save cleaned files
to output directory, specify that directory as the last file:

```
mkdir out
whiteboardcleaner image1.png image2.jpg out
```

# Requirements

* C++11 compiler
* Boost (with `program_options` and `filesystem`)
* ImageMagick

# License

[Apache 2.0](LICENSE)
