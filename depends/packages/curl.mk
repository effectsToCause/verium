package=curl
$(package)_version=7.62.0
$(package)_download_path=https://curl.haxx.se/download/
$(package)_file_name=$(package)-$($(package)_version).tar.gz
$(package)_sha256_hash=55ccd5b5209f8cc53d4250e2a9fd87e6f67dd323ae8bd7d06b072cfcbb7836cb
$(package)_dependencies=openssl

define $(package)_set_vars
$(package)_config_opts=--disable-shared
$(package)_cxxflags=-std=c++11

endef

define $(package)_config_cmds
  ./buildconf && \
  $($(package)_autoconf)
endef

define $(package)_build_cmds
  $(MAKE)
endef

define $(package)_stage_cmds
  $(MAKE) DESTDIR=$($(package)_staging_dir) install
endef
