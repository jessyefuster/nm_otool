./ft_otool $@ > ftotool_result
otool -t $@ > otool_result
diff ftotool_result otool_result
rm ftotool_result otool_result
