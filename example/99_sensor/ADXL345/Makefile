all: so
	gcc -Wall -o main main.c -ldl

so:
	gcc ADXL345.c -fPIC -shared -o ADXL345.so

clean:
	rm -rf ADXL345.so main
