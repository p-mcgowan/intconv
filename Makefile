all: intconv.cpp intconv.h; g++ intconv.cpp -o conv
clean: rm conv