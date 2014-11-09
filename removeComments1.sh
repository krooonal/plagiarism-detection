[ $# -eq 2 ] && arg="$1" || arg=""
eval file="\$$#"
sed 's/#[ \t\n]*include/__LIB/g' $file |
          gcc -w -P -E $arg - |
          sed 's/__LIB/#include/'
