MAKE = make

all: engine

clean: engine_clean

engine:
	$(MAKE) -C src/engine
	
engine_clean:
	$(MAKE) -C src/engine clean

install:
	cp -r src/* /var/www/html/
