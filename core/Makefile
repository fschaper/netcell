#
# Linux Makefile
#
# Author:
# Radu Racariu <radu@yalos-solutions.com>
# Florian Schaper <florian.schaper@jedox.com>
# Jedox AG, Freiburg, Germany
#
include Makefile.inc
DEPLOY_DIR := ./build
EXTENSION_DIR := $(DEPLOY_DIR)/extension
PHP_EXTENSION_DIR := $(DEPLOY_DIR)/php_extensions
EXTLIBS_DIR := $(DEPLOY_DIR)/lib
CONFIG_DIR := $(DEPLOY_DIR)/etc

ifneq "$(filter deploy,$(MAKECMDGOALS))" "deploy"
all:
	$(MAKE) -C server/src
	$(MAKE) -C extensions/function/src
	$(MAKE) -C extensions/ui_backend/src
	$(MAKE) -C extensions/persistence/src
	$(MAKE) -C extensions/text_metrics/src
	$(MAKE) -C extensions/palo/src
	$(MAKE) -C extensions/cell_format/src
	$(MAKE) -C extensions/macro_engine/src
	$(MAKE) -C extensions/auto_fill/src
	$(MAKE) -C extensions/odbc/src	
	@echo "make all DONE."
endif

deploy: all
	mkdir -p $(DEPLOY_DIR)
	mkdir -p $(EXTENSION_DIR)
	mkdir -p $(CONFIG_DIR)
	mkdir -p $(EXTLIBS_DIR)
	mkdir -p $(PHP_EXTENSION_DIR)
	cp -u ./server/bin/run.sh $(DEPLOY_DIR)
	cp -u ./server/etc/config.xml $(CONFIG_DIR)
	cp -u ./extensions/text_metrics/xml/font_config.xml $(CONFIG_DIR)
	sed -i 's/extension\\//g' $(CONFIG_DIR)/config.xml
	sed -i 's/="function/ = "function_library/g' $(CONFIG_DIR)/config.xml
	sed -i 's/C:\/WINDOWS\/Fonts/var\/fonts/g' ./build/etc/font_config.xml 
	sed -i 's/config="/config = "etc\//g' $(CONFIG_DIR)/config.xml
	cp -u ./extensions/palo/xml/palo_config.xml $(CONFIG_DIR)
	cp -u ./extensions/macro_engine/xml/macro_engine_config.xml $(CONFIG_DIR)
	cp -u ./extensions/ui_backend/xml/ui_backend_config.xml $(CONFIG_DIR)
	cp -u ./extensions/persistence/xml/persistence_settings.xml $(CONFIG_DIR)
	sed -i 's/..\/httpd\/app\/base;/..\/httpd\/app\/base:/g' $(CONFIG_DIR)/macro_engine_config.xml
	sed -i 's/..\/httpd\/app\/lib;/..\/httpd\/app\/lib:/g' $(CONFIG_DIR)/macro_engine_config.xml
	sed -i 's/eAccelerator_ts.dll/eaccelerator.so/g' $(CONFIG_DIR)/macro_engine_config.xml
	cp -u -R ./server/xml/locale $(CONFIG_DIR)
	rm -rf `find $(CONFIG_DIR) -type d -name .svn`
	find ./extlibs/ -wholename "*$(LIBDIR)" -exec find {}/ \( -iname "*.so*" ! -iname "*.svn*" \) \; |  xargs -i cp -u -R {} $(EXTLIBS_DIR)/
	cp -u ./server/src/core.bin $(DEPLOY_DIR)
	find ./extensions/ -name "*.so" -type f -exec cp -u {} $(EXTENSION_DIR)/ \;
	mv -f -u $(EXTLIBS_DIR)/libphp_jedox_palo.so* $(PHP_EXTENSION_DIR)/
	mv -f -u $(EXTLIBS_DIR)/eaccelerator.so* $(PHP_EXTENSION_DIR)/
	mkdir -p -m 777 $(DEPLOY_DIR)/tmp
	@echo "make deploy DONE."

clean_binary:
	find ./extensions/ -name "*.so" -type f -exec rm -f {}/ \;
	rm -f ./server/src/*.bin
	@echo "make clean_binary DONE."

remove_build:
	make clean
	rm -f -R $(DEPLOY_DIR)

clean:
	$(MAKE) -C server/src clean
	$(MAKE) -C extensions/function/src clean
	$(MAKE) -C extensions/ui_backend/src clean
	$(MAKE) -C extensions/persistence/src clean
	$(MAKE) -C extensions/text_metrics/src clean
	$(MAKE) -C extensions/palo/src clean
	$(MAKE) -C extensions/cell_format/src clean
	$(MAKE) -C extensions/macro_engine/src clean
	$(MAKE) -C extensions/auto_fill/src clean
	$(MAKE) -C extensions/odbc/src clean
	@echo "make clean DONE."