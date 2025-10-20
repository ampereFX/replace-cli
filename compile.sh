#!/usr/bin/env bash

out="o/replace"
compilation_log="compilation.log"

outpath=$(echo $out)
outdir=$(dirname $outpath)

mkdir -p "$outdir"
# gcc replace.c -v --output="$out" > "$compilation_log" 2>&1; echo ""
clang -v -g -O0 replace.c -o "$out" > "$compilation_log" 2>&1

if [ $? = "0" ]; then
    echo "Compiled successfully!"
    echo "Won't show compilation log"
    echo -e "(but it's saved under \"$compilation_log\")\n"
    chmod +x "$outpath"
    if [ "$1" = "--and-run-using" ]; then
        echo "Running compiled binary using:"
        echo -e "$(echo $outpath | sed s"|$(pwd)|.|")\
            $(echo "$*" | sed s'|--and-run-using||')\n"
        "$outpath" "$2" "$3" "$4" "$5" "$6" "$7" "$8" "$9" 
    fi
else
    echo "Compilation failed."
    echo "Do you want to look at the log? (y/n): "
    read answer
    if [ "$answer" = y ]; then cat "$compilation_log"; fi
fi
echo "--------------"

