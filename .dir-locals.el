((nil . ((format-all-formatters . (("C++" clang-format)))))
 (c++-ts-mode
  (c-ts-mode-indent-offset . 4)
  (flycheck-cppcheck-standards      . "c++20")
  (flycheck-clang-language-standard . "c++20")
  (flycheck-gcc-language-standard   . "c++20"))
 (c++-ts-mode
  (eval add-hook 'before-save-hook #'format-all-buffer nil 'local)))
