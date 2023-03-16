user=$( pwd | cut -d"/" -f4)

for logfile in log*.txt
do
   tmp=${logfile#*_}
   idx=${tmp%.*}
   out=$( grep FileOpenError $logfile )
   if [[ $out == "An exception of category 'FileOpenError' occurred while" ]]; then
      echo "resubmitting job num $idx"
      /home/llr/cms/$user/t3submit -short job_$idx.sh
   fi
done
