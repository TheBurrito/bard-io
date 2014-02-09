#The following capitalized variables store the command-line commands to perform various functions
#The lower cased rules following include controlling the verbosity of these commands and should not
#be changed.

CC=$(CROSS_COMPILE)gcc $(CFLAGS)
CXX=$(CROSS_COMPILE)g++ $(CXXFLAGS)
LD=$(CROSS_COMPILE)g++ $(LDFLAGS)
AR=$(CROSS_COMPILE)ar $(ARFLAGS)
RM=rm -rf
CP=cp -r
MV=mv
MKDIR=mkdir -p

rm=$(quiet)$(RM)
cp=$(quiet)$(CP)
mv=$(quiet)$(MV)
mkdir=$(quiet)$(MKDIR)

makeopts=
make=@$(MAKE) $(makeopts)

log=$(if $(quiet),,$(warning $1))
local=$(subst $(CURDIR)/,,$1)

define cc
	@echo "    CC $(notdir $@)"
	$(quiet)  $(CC) -o $(BUILD_DIR)/$(subst .c,.o,$(notdir $^)) -c $(call local,$^)
endef

define cxx
	@echo "    CXX $(notdir $@)"
	$(quiet)  $(CXX) -o $(BUILD_DIR)/$(subst .cpp,.o,$(notdir $^)) -c $(filter-out %.a,$(call local,$^))
endef

define ld
	@echo "    LD $@"
	$(quiet)  $(LD) -o $(BUILD_DIR)/$@ $(foreach file,$(call local,$^),$(BUILD_DIR)/$(notdir $(file)))
	$(mv) $(BUILD_DIR)/$@ $(BIN_DIR)
endef

define ar
	@echo "    AR $@"
	$(quiet)  $(AR) $(BUILD_DIR)/$@ $(foreach file,$(call local,$^),$(BUILD_DIR)/$(notdir $(file)))
	$(cp) $(BUILD_DIR)/$@ $(LIB_DIR)
endef
