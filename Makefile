.PHONY: scannertest run test lldb

cc := clang++
flex := flex++
bison := bison3
prom := cmm

inc_dir := include
src_dir := src
obj_dir := obj
bin_dir := bin
test_dir := testcase
bison_dir := bison

INC := -I$(inc_dir) -I$(bison_dir)

headers = $(shell find $(inc_dir) -name "*.h" -or -name "*.hh")
scanner_test = scannertest.cc
srcs = $(shell find $(src_dir) -name "*.cc" -not -name "$(scanner_test)" -not -name "main.cc")
obj = $(srcs:%.cc=%.o)
obj_file = $(addprefix $(obj_dir)/, $(notdir $(obj)))
bin = $(bin_dir)/$(prom)
scanner_test_bin = $(bin_dir)/scannertest

obj_count = $(shell echo $(obj) | wc -w)
cnt = 0

all: bison_prep $(prom)

include bison/Makefile.part

$(bin):
	@echo "\033[1;32mUse \`make\` to build $(bin).\033[0m"
	@exit 1

$(prom): $(obj_file) bison_obj $(obj_dir)/main.o 
	@printf	"[%3d%%] " $$(($(cnt) * 100 / ($(obj_count)+1)))
	@echo "\033[1;32mBuilding target...\033[0m"
	@$(cc) $(CXXFLAGS) -g -lcurses -o $(bin) $(scanner_obj) $(parser_obj) $(driver_obj) $(obj_file) $(obj_dir)/main.o
	@echo "[100%] Built target $(bin)"

scannertest: $(scanner_file) $(parser_file) $(obj_file) $(src_dir)/$(scanner_test)
	@printf	"[%3d%%] " $$(($(cnt) * 100 / ($(obj_count)+1)))
	@echo "\033[1;32mBuilding target...\033[0m"
	@$(cc) $(CXXFLAGS) -g -o $(scanner_test_bin) $(INC) $(obj_file) $(src_dir)/$(scanner_test)
	@echo "[100%] Built target $(scanner_test_bin)"
	@$(scanner_test_bin)

$(obj_dir)/main.o: $(src_dir)/main.cc $(headers)
	@printf	"[%3d%%] " $$(($(cnt) * 100 / ($(obj_count)+1)))
	@echo "\033[32mBuilding object $@...\033[0m"
	$(eval cnt = $(shell echo $$(($(cnt)+1))))
	@$(cc) $(CXXFLAGS) -g $(INC) -c $< -o $(obj_dir)/$(notdir $@)

$(obj_file): $(obj_dir)/%.o: $(src_dir)/%.cc $(headers)
	@printf	"[%3d%%] " $$(($(cnt) * 100 / ($(obj_count)+1)))
	@echo "\033[32mBuilding object $(obj_dir)/$(notdir $@)...\033[0m"
	$(eval cnt = $(shell echo $$(($(cnt)+1))))
	@$(cc) $(CXXFLAGS) -g $(INC) -c $< -o $(obj_dir)/$(notdir $@)

lldb: $(bin)
	@echo "\033[1;33mStart Debugging With LLDB...\033[0m"
	@lldb -f $(bin)

run: $(bin)
	@echo "\033[1;36mRunning...\033[0m"
	@$(bin)

test: $(bin)
	@echo "\033[36mFiles in directory \`testcase\`:\033[0m"
	@ls $(test_dir) | awk -v RS='' '{for(i=1;i<=NF;i++) printf("%d \033[1;33m%s\033[0m\n", i, $$i)}'
	@printf "\033[36mEnter test file name number: \033[0m"
	@files_list=($(test_dir)/*);\
	read test_file_name; \
	$(bin) $${files_list[test_file_name-1]}

clean: clean-bison
	@echo "\033[1;31mRemoving targets...\033[0m"
	@-rm -rf $(obj_dir)/* 2>/dev/null 
	@-rm -rf $(scanner_test_bin) 2> /dev/null
	@-rm -rf $(bin) 2> /dev/null
	@echo "Removed"
