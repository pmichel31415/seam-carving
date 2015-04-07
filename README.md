#Seam-Carving

Seam-carving was originally a project for a course at [École polytechnique](http://www.polytechnique.edu/).

It is a CLI program implementing various algorithms around the idea of seam-carving, a very interesting method for 1-dimension image resizing (see [this video](https://www.youtube.com/watch?v=6NcIJXTlugc) for instance).

If you want to test the program please visit [SCTest](sctest.mandrathax.fr).

##Install

*Requirements : you must have [openCV](opencv.org) installed in order to run this program*

Just clone the repo and let the CMake magic do its job, just don't forget to specify the $OPENCV_DIR variable :

    $git clone https://github.com/Mandrathax/seam-carving.git
	$cmake -G 'Unix Makefiles' .
	$make

for instance on linux

You can find CMake [here](www.cmake.org).

##Use

Right now the program must be used this way :

	$seam-carving <path-to-source> <target-width>x<target-height> <path-to-output> <algo> <opt>

Where `<algo>` is either :

- `1` for "backward propagation" dynamic algorithm
- `2` for "forward propagation" dynamic algorithm
- `3` for the random algorthm, where `<opt>` is then the number of tries for each seam (50-100 generally gives good results

##Credit

- [Paul Michel](https://github.com/Mandrathax) : Random algo and demo website SCTest
- [Antoine Prouvost](https://github.com/AntoinePrv) : Dynamic algos

**Warning :** This project is still a beta : algo 2 doesn't work yet and the code is not as clean as it should be.
