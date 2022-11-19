set tabstop=4
set softtabstop=4
set shiftwidth=4
set noexpandtab

set colorcolumn=100
highlight ColorColumn ctermbg=darkgray

augroup project
  autocmd!
  autocmd BufRead,BufNewFile *.h,*.c set filetype=c | set syntax=c.doxygen
augroup END

let &path.="src,"

