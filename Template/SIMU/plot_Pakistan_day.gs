'reinit'

*'sdfopen EARLY-2020.nc'
'open HS.ctl'
*'open GSMAP_DAY_SL_CORR.ctl'

**** Open the numerical model file
'set mpdset hires'
*'set lon 79.5 82.0'
*'set lat  6 9.5'

*X is varying   Lon = 22.95 to 37.05   X = 230 to 371
*Y is varying   Lat = -5.05 to 16.05   Y = 550 to 761



'set map 1 0 4'
'set parea 1.5 9.8 1.25 7.75'


tt=01

while (tt<=60)



'set dfile 1'
'set t ' tt
'q dim'
line=sublin(result,5);tims=subwrd(line,6)
tims1=substr(tims,4,11)
ttt=tims1

say tims

*'run subplot.gs 2 1 2 -xtight 1 -ytight 1'

'set time ' ttt
'set xlint 1'
'set ylint 1'
*'set lon 61 75'
*'set lat  24 37'
'set grads off'
*'set xlopts 1 4 0.25'
*'set ylopts 1 4 0.25'
*'set lon 22 38'
*'set lat -5 17'
*'set lon 24 36'
*'set lat 4 12'
'run color1.gs 0 2 0.2 -kind white->lightskyblue->blue->red->magenta' 
'set gxout grfill'

'd pr'
'set string 1 c 5.5'; 'set strsiz 0.25'; 'draw string 5.5 8.0 Simulated Inundation: 'ttt
'cbarn 1 1 9.2'
'set string 1 c 5.5'; 'set strsiz 0.1'; 'draw string 9.4 7.8 [m]'


*'set string 1 c 5.5'; 'set strsiz 0.2'; 'draw string 3.7 7.8 Before (mm/day): 'ttt

*'set dfile 2'
*'set time 'ttt
*'set lon 79.5 82.5'
*'set lat  5.75 10.0'
*'set lon 79.75 80.75'
*'set lat  6.25 7.25'
*'set lon 79.5 82.0'
*'set lat  6 9.5'
*'set line 1 1 6'
*'set grads off'
*'set digsiz 0.8'
*
*'set cmark 2'
*'set gxout stnmark'
*'set stid off'

*'set gxout value'
*'Set ccolor 6'
*'set dignum 0'
*'set digsiz 0.1'

*'d rain.2'

'set line 1 1 8'
*'draw shp cell_are_poli'
*'set line 1 1 8'
*'draw shp Kaleni'


*say "plot 2nd "
*'set dfile 3'
*'set time 'ttt
*'set xlint 0.25'
*'set ylint 0.25'
*'set grads off'
**'run subplot.gs 2 2 2 -xtight 1 -ytight 1'
*'run color1.gs 0 100 5 -kind white->lightskyblue->blue->red->magenta' 
*'set gxout grfill'
*'d rainnc.3'
*'set string 1 c 5.5'; 'set strsiz 0.2'; 'draw string 3.7 7.8 After (mm/day): 'ttt
*
*
*
*'set dfile 2'
*'set time 'ttt
*'set lon 79.9 80.75'
*'set lat  6.25 7.0'
*'set line 1 1 6'
*'set grads off'
*'set digsiz 0.8'
*
*'set cmark 2'
*'set gxout stnmark'
*'set stid off'
*
*'set gxout value'
*'Set ccolor 6'
*'set dignum 0'
*'set digsiz 0.25'

*'d rain.2'
*'set line 1 1 8'
*'draw shp Kalu'
*'cbarn 1 2.5 9.5'
*
if (tt < 10)
filename = 'HS_day0'tt
else
filename = 'HS_day'tt
endif
'printim ' filename'.png white'
'c'
tt=tt+1
endwhile

'set xlint 1'
'set ylint 1'
*'set lon 24 36'
*'set lat 4 12'
'run color1.gs 0 2 0.2 -kind white->lightskyblue->blue->red->magenta'
'set gxout grfill'

'd max(pr, time = 01Aug2024,time=30sep2024)'
'set string 1 c 5.5'; 'set strsiz 0.25'; 'draw string 5.5 8.0 INUNDATION 01Aug2024-30Sep2024 '
'cbarn 1 1 9.3'
'set string 1 c 5.5'; 'set strsiz 0.1'; 'draw string 9.4 7.8 [mm]'

'printim HR_MAX.png white'
'c

