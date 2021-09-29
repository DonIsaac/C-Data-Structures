echo "Checking if dependencies are installed..."
for dep in $@; do
    if [ $(which $dep > /dev/null) ] ; then
        echo "$dep binary is not installed. You can install it with 'make check'."
        exit 1
    fi
done
