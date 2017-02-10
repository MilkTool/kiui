//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_STRIPE_H
#define TOY_STRIPE_H

/* toy */
#include <toyui/Frame/Frame.h>

/* std */
#include <vector>

namespace toy
{
	typedef std::vector<Frame*> FrameVector;

	class TOY_UI_EXPORT FlowSequence
	{
	public:
		FlowSequence(FrameVector& vec) : d_vector(vec), d_size(0) {}
		FlowSequence& operator=(const FlowSequence&) = delete;
		FrameVector::const_iterator begin() { return d_vector.begin(); }
		FrameVector::const_iterator end() { return d_vector.begin() + d_size; }
		FrameVector::reverse_iterator rbegin() { return d_vector.rbegin() + (d_vector.size() - d_size); }
		FrameVector::reverse_iterator rend() { return d_vector.rend(); }
		size_t& size() { return d_size; }
		typedef FrameVector::reverse_iterator reverse_iterator;
	private:
		FrameVector& d_vector;
		size_t d_size;
	};

	class TOY_UI_EXPORT Stripe : public Frame
	{
	public:
		Stripe(Widget& widget);
		Stripe(StyleType& style, Stripe& parent);

		FrameType frameType() { return STRIPE; }

		inline FrameVector& contents() { return d_contents; }
		inline FlowSequence& sequence() { return d_sequence; }

		inline float spacing(Frame& frame) { return this->before(frame) ? d_layout->spacing()[d_length] : 0.f; }
		
		inline float alignSequence(Frame& frame, float space) { return space * AlignSpace[frame.dalign(d_length)]; }

		inline float dpivotposition(Frame& frame, Dimension dim) { return d_layout->pivot()[dim] ? dsize(dim) - frame.dsize(dim) - frame.dposition(dim) : frame.dposition(dim); }

		virtual void map(Frame& frame);
		virtual void unmap(Frame& frame);
		virtual void remap();

		void append(Frame& frame);
		void insert(Frame& frame, size_t index);
		void remove(Frame& frame);
		void clear();

		void reindex(size_t from);
		void move(size_t from, size_t to);

		Frame* before(Frame& frame);
		Frame& prev(Frame& frame);
		Frame& next(Frame& frame);
		bool first(Frame& frame);
		bool last(Frame& frame);

		virtual void measure();
		void measure(Frame& frame, DimFloat& content);

		virtual void layout();
		void resize(Frame& frame, DimFloat& expanded);
		void layout(Frame& frame, DimFloat& offset, DimFloat& space);

		float resize(Frame& frame, Dimension dim);

		void position(Frame& frame, DimFloat& offset, DimFloat& space);
		float positionFree(Frame& frame, Dimension dim, float offset, float space);
		float positionSequence(Frame& frame, float offset, float space);

		void normalizeSpan();

		float nextOffset(Dimension dim, float pos);
		float prevOffset(Dimension dim, float pos);

		Frame* pinpoint(float x, float y, bool opaque);

	protected:
		FrameVector d_contents;
		FlowSequence d_sequence;
	};
}

#endif // TOY_SEQUENCECONTAINER_H