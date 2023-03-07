# 42 ft_printf

printf を再実装

`int ft_printf(const char *argv, ...);`

- 変換指定子
  - c- char
  - s- string
  - p- pointer
  - d- int
  - i- int
  - u- unsigned int
  - x- hex
  - X- hex (large alpha)
  - %- percent char
- フラグ類
  - 0
  - \*
  - 最小フィールド幅
  - 精度

## Sample script

```zsh
git clone https://github.com/Masaya-Kamei/ft_printf.git --recursive
cd ft_printf
make
gcc -w main/main.c -I./includes -L. -lftprintf
echo -e "\n---Output---"
./a.out
```

## Tool

- [my libft](https://github.com/Masaya-Kamei/libft) (42 useful functions)
- [42TESTERS-PRINTF](https://github.com/Mazoise/42TESTERS-PRINTF) (42 ft_printf tester)
- [Github Actions](https://docs.github.com/ja/actions) (CI/CD tool)
