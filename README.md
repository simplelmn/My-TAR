# Welcome to My Tar
***

## Task
my_tar is a command to manipulate tape archive. The first option to tar is a mode indicator from the following list:

-c Create a new archive containing the specified items.
-r Like -c, but new entries are appended to the archive. The -f option is required.
-t List archive contents to stdout.
-u Like -r, but new entries are added only if they have a modification date newer than the corresponding entry in the archive. The -f option is required.
-x Extract to disk from the archive. If a file with the same name appears more than once in the archive, each copy will be extracted, with later copies overwriting (replacing) earlier copies.
In -c, -r, or -u mode, each specified file or directory is added to the archive in the order specified on the command line. By default, the contents of each directory are also archived.

Unless specifically stated otherwise, options are applicable in all operating modes:

-f file Read the archive from or write the archive to the specified file. The filename can be standard input or standard output.
my_tar will not handle file inside subdirectory.

## Description
firstly we read some documentations about tar files, and checked all given functions in subject, learned how to use posix header. Finally we have done the task.

## Installation
It depends on your OS, if you use Unix-like systems, just use Makefile. Otherwise you should install GNU OS.

## Usage
You can compile with following options
```
./my_tar -cf file_name.tar file1 file2
./my_tar -tf file_name.tar
./my_tar -rf file_name.tar file3
./my_tar -uf file_name.tar file4
./my_tar -xf file_name.tar
 
```

### The Core Team


<span><i>Made at <a href='https://qwasar.io'>Qwasar Silicon Valley</a></i></span>
<span><img alt='Qwasar Silicon Valley Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px'></span>
# My-TAR
