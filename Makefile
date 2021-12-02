.PHONY: 1_blinky_minimal 2_blinky 3_blinky_cube 4_blinky_another

all: 1_blinky_minimal 2_blinky 3_blinky_cube 4_blinky_another
	echo "some"

1_blinky_minimal:
	$(MAKE) -C 1_blinky_minimal
2_blinky:
	$(MAKE) -C 2_blinky
3_blinky_cube:
	$(MAKE) -C 3_blinky_cube
4_blinky_another:
	$(MAKE) -C 4_blinky_another

clean:
	$(MAKE) -C 1_blinky_minimal clean
	$(MAKE) -C 2_blinky clean
	$(MAKE) -C 3_blinky_cube clean
	$(MAKE) -C 4_blinky_another clean