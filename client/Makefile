# program adı
NAME		= uchat

# Kaynak klasör dosya adı
SRC_DIR		= src/
# Kaynak Obje Dosya Adı
OBJ_DIR		= obj/
# Header için oluşturulmuş ana dosya adı
INC_DIR		= inc/
# src/ için alt klasöö
DIRS		= $(notdir $(wildcard $(SRC_DIR)*))
# Sadece C dosyalarının bulunduğu liste
FILES		= $(foreach dir, $(DIRS), $(basename $(wildcard \
			  $(SRC_DIR)$(dir)/*.c)))
# Dosyalara .c uzantısı atama
SRC			= $(FILES:%=%.c)
# Dosyalara .o uzantısını atama
OBJ			= $(SRC:src/%.c=$(OBJ_DIR)%.o)
# Başlık dosyasının listesi
INC_H		= $(wildcard $(INC_DIR)*.h)

# Kütüphane ile ana klasör
LIB_DIR		= ../libs
# Tüm kütüphanelerin liste adı
LIB_LIST	= $(notdir $(wildcard $(LIB_DIR)/*))
# Kütüphane oluşturma 
LIB_DIRS	= $(foreach libdirs, $(LIB_LIST), $(LIB_DIR)/$(libdirs)/)
# Dosya yolu oluşturma
LIB_BIN		= $(join $(LIB_DIRS), $(addsuffix .a, $(LIB_LIST)))

LIB_INC		= $(addsuffix $(INC_DIR), $(LIB_DIRS))

# compiler
CC			= clang
# Compiler kuralı
GFLAGS		= -std=c11 -pipe -Wall -Wextra -Werror -Wpedantic\
	-Wno-unused-command-line-argument -Wno-unused-variable \
	-Wno-unused-function -Wno-unused-parameter -g3 -fsanitize=address,undefined \
	-fno-omit-frame-pointer -O0
# Özel compiler
CFLAGS		= `pkg-config --cflags --libs gtk+-3.0`
# Header dosyası ile klasör
IFLAGS		= $(addprefix -I, $(LIB_INC) $(INC_DIR))

COMPILE		= $(CC) $(GFLAGS) $(IFLAGS) $(CFLAGS) $(LIB_BIN)
MAKE_M		= make -sf Makefile -C
MKDIR		= mkdir -p
RM			= /bin/rm -rf

all: $(LIB_LIST) $(NAME)
$(NAME): $(OBJ_DIR) $(OBJ) $(LIB_BIN)
	@$(COMPILE) $(OBJ) -lmx -o $(NAME)
	@printf "\r\33[2K$@ \033[32;1mcreated\033[0m\n"

# Tüm kütüphaneleri oluştur
$(LIB_LIST): $(LIB_DIRS)
	@$(MAKE_M) $(LIB_DIR)/$@

# OBJ dosyaları için klasörleri oluştur
$(OBJ_DIR):
	@$(MKDIR) $@ $(foreach dir, $(DIRS), $@/$(dir))


$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC_H)
	@$(COMPILE) -o $@ -c $<
	@printf "\r\33[2K$(NAME) \033[33;1mcompile \033[0m$(<:$(SRC_DIR)/%.c=%) "

clean:
	@$(RM) $(OBJ_DIR)
	@printf "$(OBJ_DIR)\t   \033[31;1mdeleted\033[0m\n"

uninstall:
	@$(RM) $(OBJ_DIR) $(NAME)
	@printf "$(NAME) \033[31;1muninstalled\033[0m\n"

reinstall: uninstall all

.PHONY: all clean uninstall reinstall
