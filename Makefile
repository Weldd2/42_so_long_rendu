# **************************************************************************** #
#                                   CONFIG                                     #
# **************************************************************************** #

NAME        = so_long
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
RM          = rm -f
RMDIR       = rm -rf

# -----------------------------------------------------------------------------
# INCLUDES
# -----------------------------------------------------------------------------
INCS        = -I include            \
              -I lib/gnl/include    \
              -I lib/io/include     \
              -I lib/mem/include    \
              -I lib/pf/include     \
              -I lib/str/include

# -----------------------------------------------------------------------------
# BIBLIOTHÈQUES ADDITIONNELLES (MLX, etc.)
# -----------------------------------------------------------------------------
LIBS        = MLX42/build/libmlx42.a -lglfw -lm -ldl -lpthread

# **************************************************************************** #
#                              SOURCES PRINCIPAUX                              #
# **************************************************************************** #
# On énumère tous les .c de src/
SO_LONG_SRCS = \
src/so_long.c \
src/core/error.c \
src/graphics/graphics.c \
src/graphics/images/images.c \
src/graphics/input/input.c \
src/map/map.c \
src/validate/bfs/bfs.c \
src/validate/bfs/queue.c \
src/validate/is_closed.c \
src/validate/is_finishable.c \
src/validate/is_playable.c \
src/validate/is_rectangular.c \
src/validate/validate.c

# **************************************************************************** #
#                              LIB : GNL                                       #
# **************************************************************************** #
GNL_SRCS = \
lib/gnl/src/gnl_get_next_line.c

# **************************************************************************** #
#                              LIB : IO                                        #
# **************************************************************************** #
IO_SRCS = \
lib/io/src/io_count_line.c \
lib/io/src/io_line_length.c \
lib/io/src/io_putchar_fd.c \
lib/io/src/io_putendl_fd.c \
lib/io/src/io_putnbr_fd.c \
lib/io/src/io_putstr_fd.c

# **************************************************************************** #
#                              LIB : MEM                                       #
# **************************************************************************** #
# Sous-dossiers : arena, classic, mgc
MEM_SRCS = \
lib/mem/src/arena/mem_arena.c \
lib/mem/src/arena/mem_arena_alloc.c \
lib/mem/src/arena/mem_arena_calloc.c \
lib/mem/src/arena/mem_arena_free.c \
lib/mem/src/arena/mem_arena_realloc.c \
lib/mem/src/classic/mem_bzero.c \
lib/mem/src/classic/mem_calloc.c \
lib/mem/src/classic/mem_free.c \
lib/mem/src/classic/mem_freetab.c \
lib/mem/src/classic/mem_malloc.c \
lib/mem/src/classic/mem_memchr.c \
lib/mem/src/classic/mem_memcmp.c \
lib/mem/src/classic/mem_memcpy.c \
lib/mem/src/classic/mem_memmove.c \
lib/mem/src/classic/mem_memset.c \
lib/mem/src/classic/mem_realloc.c \
lib/mem/src/mgc/mem_mgc.c \
lib/mem/src/mgc/mem_mgc_alloc.c \
lib/mem/src/mgc/mem_mgc_calloc.c \
lib/mem/src/mgc/mem_mgc_free.c

# **************************************************************************** #
#                              LIB : PF (printf)                               #
# **************************************************************************** #
PF_SRCS = \
lib/pf/src/pf_handle.c \
lib/pf/src/pf_printf.c \
lib/pf/src/pf_utils.c \
lib/pf/src/pf_utils2.c

# **************************************************************************** #
#                              LIB : STR                                       #
# **************************************************************************** #
STR_SRCS = \
lib/str/src/cat/str_strcat_until.c \
lib/str/src/cat/str_strlcat.c \
lib/str/src/copy/str_strcpy_until.c \
lib/str/src/copy/str_strlcpy.c \
lib/str/src/search/str_strchr.c \
lib/str/src/search/str_strcontains.c \
lib/str/src/search/str_strendwith.c \
lib/str/src/search/str_strequals.c \
lib/str/src/search/str_strncmp.c \
lib/str/src/search/str_strnstr.c \
lib/str/src/search/str_strstartwith.c \
lib/str/src/str_split.c \
lib/str/src/str_strdup.c \
lib/str/src/str_striteri.c \
lib/str/src/str_strjoin.c \
lib/str/src/str_strlen.c \
lib/str/src/str_strmapi.c \
lib/str/src/str_strrchr.c \
lib/str/src/str_strsplitchar.c \
lib/str/src/str_strtrim.c \
lib/str/src/sub/str_extract_sub.c \
lib/str/src/sub/str_replace_sub.c \
lib/str/src/sub/str_slice.c

# **************************************************************************** #
#                    LISTE GLOBALE DES SOURCES ET DES OBJETS                   #
# **************************************************************************** #

SRCS        = $(SO_LONG_SRCS) $(GNL_SRCS) $(IO_SRCS) $(MEM_SRCS) $(PF_SRCS) $(STR_SRCS)
OBJS        = $(SRCS:.c=.o)

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

# -----------------------------------------------------------------------------
# Règle par défaut : all
# -----------------------------------------------------------------------------
all: $(NAME)

# -----------------------------------------------------------------------------
# Compilation de l'exécutable final
# -----------------------------------------------------------------------------
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCS) $^ $(LIBS) -o $@

# -----------------------------------------------------------------------------
# Compilation des .c en .o
# -----------------------------------------------------------------------------
%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

# -----------------------------------------------------------------------------
# Nettoyage des fichiers objets
# -----------------------------------------------------------------------------
clean:
	$(RM) $(OBJS)

# -----------------------------------------------------------------------------
# Nettoyage complet (exécutable + objets)
# -----------------------------------------------------------------------------
fclean: clean
	$(RM) $(NAME)

# -----------------------------------------------------------------------------
# Recompilation totale
# -----------------------------------------------------------------------------
re: fclean all

# -----------------------------------------------------------------------------
# Installation MLX42 (submodule) - si nécessaire
# -----------------------------------------------------------------------------
install:
	git submodule init
	git submodule update
	@echo "Submodules initialized/updated."

mlx_install:
	git clone https://github.com/codam-coding-college/MLX42.git
	$(MAKE) mlx_build

mlx_build:
	cd MLX42 && rm -rf build && \
	cmake -B build -DGLFW_DIR=/opt/homebrew/lib/cmake/glfw3 && \
	cmake --build build -j4

# -----------------------------------------------------------------------------
# Règles de debug, valgrind
# -----------------------------------------------------------------------------
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all \
                 --suppressions=valgrind_files/so_long.supp \
                 --suppressions=valgrind_files/mlx42.supp
TEST_ARGUMENTS = map.ber

valgrind: CFLAGS += -g
valgrind: re
	valgrind $(VALGRIND_FLAGS) ./$(NAME) $(TEST_ARGUMENTS)

debug: CFLAGS += -g
debug: re

# -----------------------------------------------------------------------------
# Déclaration des règles phony
# -----------------------------------------------------------------------------
.PHONY: all clean fclean re install mlx_install mlx_build debug valgrind
