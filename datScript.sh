#! /bin/bash
# This is comment line; #! is called Shebang -> executable in a Unix-like operating system. 
# Please run in Bash shell by: $ datScript.sh
# Try "$ dos2unix datScript.sh" in Linux if "Syntax error: unexpected end of file" occurs.
echo running script...

echo -n "Please input width of rectangle(positive integer):"
read w
if [[ ! $w =~ ^[0-9]+$ ]] ; then
    echo "invalid input! Exit with code -1"
    exit -1
fi
if test $w -le 0
then
  echo "invalid input w=$w! Exit with code 1"
  exit 1
fi

echo -n "Please input height of rectangle(positive integer):"
read h
if [[ ! $h =~ ^[0-9]+$ ]] ; then
    echo "invalid input! Exit with code -1"
    exit -1
fi
if [ $h -le 0 ]
then
  echo "invalid input h=$h ! Exit with code 1"
  exit 1
fi

echo -n "Please input safe region start column of rectangle(positive integer <= `expr ${w} - 2`):"
read safeS
if [[ ! $safeS =~ ^[0-9]+$ ]] ; then
    echo "invalid input! Exit with code -1"
    exit -1
fi
if (($safeS>=$((${w} - 1)) )) || (($safeS<=0)) 
then
  echo "invalid input safeS=$safeS ! Exit with code 1"
  exit 1
fi

echo -n "Please input safe region width of rectangle(positive integer <= $((w-safeS - 1)) ):"
read safeW
if [[ ! $safeW =~ ^[0-9]+$ ]] ; then
    echo "invalid input! Exit with code -1"
    exit -1
fi
if (($safeW>$((w-safeS - 1)) )) || (($safeW<=0)) 
then
  echo "invalid input safeW=$safeW ! Exit with code 1"
  exit 1
fi


echo "Now input (($h*$w)) pixel values(-1 to -16777216 inclusive integers)"
values=()
for ((i=0;i<(($h*$w));i++ ))
do
  while :
  do
    echo -n "Please input No.$((${i}+1)) value(-1 to -16777216 inclusive integers): "
    read values[i]
    # [[ ${values[i]} =~ ^[0-9]+$ ]] <- this is for non-negative integer
    if [[ ${values[i]} =~ ^(-)?[0-9]+$ ]] && ((${values[i]}<= -1)) && ((${values[i]}>= -16777216))
    then
      break
    fi
    
    echo "Invalid input, please input again."
  done

done

echo "all inputted values are: ${values[@]}"

echo "=============== Break Line ==========================="

rm -f script_image.dat
touch script_image.dat
chmod u+rwx script_image.dat

echo -n "Data of the input file is: "
echo "$w $h $safeS $safeW ${values[@]}" >> script_image.dat
cat script_image.dat

echo "=============== Break Line ==========================="
echo "Automatically run 'gcc images.c functions.c -Wall' and 'a.out < script_image.dat'"
gcc images.c functions.c -Wall && a.out < script_image.dat


echo "=============== Break Line ==========================="
if [ $? -eq 0 ]
then
  echo NO error occurs
else
  echo please check Errors
fi
