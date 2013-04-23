Fishy: *.cpp *.hpp
	g++ -g -Wall -Werror -o Fishy *.cpp -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lGLEW -ljpeg -lXrandr -lfreetype -lpthread -lrt

tags: *.cpp *.hpp
	ctags *.cpp *.hpp

clean:
	rm Fishy
