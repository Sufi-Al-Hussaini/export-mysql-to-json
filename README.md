# export-mysql-to-json
Export mysql tables to JSON


## Build
* Using CMake: 
```sh
mkdir -p build
cd build
cmake ..
```

* Using supplied Makefile
```sh
# Set `BUILD_DIR` in Makefile
# Run make from root dir
make 
```


## Run
Pipe the output of your mysql query to `export-mysql-to-json`. This can be done from the command line like so:
```sh
mysql -u user -p*** -e "select * from <schema>.<table>;" | ./build/export-mysql-to-json
```

`export-mysql-to-json` uses column names as json keys. You can change them using Mysql's `AS` statement.
```sh
mysql -u user -p*** -e "select <column name> as <column name alias> from <schema>.<table>;" | ./build/export-mysql-to-json
```

