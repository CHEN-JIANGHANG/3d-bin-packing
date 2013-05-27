/*
 * 2dGuillotine.hpp
 *
 *  Created on: 24-05-2013
 *      Author: krris
 */

#ifndef GUILLOTINE2D_HPP_
#define GUILLOTINE2D_HPP_

#include <vector>

#include "rect.hpp"

/**
 * 2D Guillotine bin packing - algorithm for packing rectangles.
 */
class Guillotine2d {
public:
	/* Set the initial bin size to (0, 0).
	 * Calls init() to set a proper bin size. */
	Guillotine2d() : binWidth(0), binHeight(0) {}

	/* Initialize a new bin */
	Guillotine2d(int width, int height);

	/* Initialize an empty bin. */
	void init(int width, int height);

	enum FreeRectChoiceHeuristic
		{
			RectBestAreaFit,
			RectBestShortSideFit,
		};

	enum GuillotineSplitHeuristic
	{
		SplitShorterLeftoverAxis,
		SplitLongerLeftoverAxis,
		SplitShorterAxis,
		SplitLongerAxis
	};

	Rect insert(int width, int height, FreeRectChoiceHeuristic rectChoice,
				GuillotineSplitHeuristic splitMethod);

	void insert(std::vector<RectSize> &rects, FreeRectChoiceHeuristic rectChoice,
				GuillotineSplitHeuristic splitMethod);

	bool fits(int width, int heigh, FreeRectChoiceHeuristic rectChoice) const;


	std::vector<Rect>& getFreeRectangles() { return freeRectangles; }

	std::vector<Rect>& getUsedRectangles() { return usedRectangles; }

private:
	int binWidth;
	int binHeight;

	/* Stores rectangles that are packed so far */
	std::vector<Rect> usedRectangles;

	/* Stores rectangles that represents the free area of the bin; */
	std::vector<Rect> freeRectangles;

	/**
	 * Search through all free rectangles to find the best one to place
	 * a new rectangle.
	 */
	Rect findPositionForNewNode(int width, int height,
								FreeRectChoiceHeuristic rectChoice,
								int *nodeIndex) const;



	static int scoreByHeuristic(int width, int height, const Rect &freeRect,
								FreeRectChoiceHeuristic rectChoice);

	static int scoreBestAreaFit(int width, int height, const Rect &freeRect);
	static int scoreBestShortSideFit(int width, int height, const Rect &freeRect);

	/* Splits the given L-shaped free rectangle into two new free rectangles
	 * after placedRect has been placed into it. Determines the split axis by
	 * using the given heuristic. */
	void splitFreeRectByHeuristic(const Rect &freeRect, const Rect &placedRect,
								  GuillotineSplitHeuristic method);

	/* Splits the given L-shaped free rectangle into two new free rectangles
	 * along the given fixed split axis. */
	void splitFreeRectAlongAxis(const Rect &freeRect, const Rect &placedRect,
								bool splitHorizontal);
};


#endif /* GUILLOTINE2D_HPP_ */