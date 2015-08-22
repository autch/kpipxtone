
TARGET=kpipxtone

ZIP=Release/$(TARGET).kpi $(TARGET)/pxtone_include/pxtoneWin32.dll $(TARGET).txt $(TARGET).ini

$(TARGET).zip: $(ZIP)
	zip -9j $@ $^
