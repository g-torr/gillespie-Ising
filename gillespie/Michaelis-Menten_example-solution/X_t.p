
      set terminal postscript eps enhanced color font "Helvetica,20"
      set output 'dynamics.eps'
      #set terminal jpeg enhanced font "Helvetica,20"
      #set output 'dynamics.jpg'

      set   autoscale;                        # scale axes automatically
      set xtic auto;                          # set xtics automatically
      set ytic auto;                         # set ytics automatically
      set title " ";
      set xlabel "t";
      set ylabel "X(t)";
      set key outside;

	    
	#plot   for [i=2:5:1] "trajectories.dat" using 1:i title columnheader(i) with linespoints pointsize 0.5 pt 7
	plot "trajectories.dat" using 1:2 title columnheader(2) with steps lt rgb "#FFE91D63" lw 2, \
		"trajectories.dat" using 1:3 title columnheader(3) with steps lt rgb "#FF0CCE6B" lw 2, \
		"trajectories.dat" using 1:4 title columnheader(4) with steps lt rgb "#FF000000" lw 2, \
		"trajectories.dat" using 1:5 title columnheader(5) with steps lt rgb "#FF999999" lw 2
