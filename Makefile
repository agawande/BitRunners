MAKE = make

all: engine

clean: engine_clean

engine:
	$(MAKE) -C src/engine
	
engine_clean:
	$(MAKE) -C src/engine clean

install:
	cp -r src/* /var/www/html/ && chmod -R a+rw /var/www/html/engine
	
uninstall:
	rm -rf /var/www/html/*
