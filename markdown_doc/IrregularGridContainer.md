# IrregularGridContainer

**Inherits:** Container

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Usefull [GridContainer] for [ExpandableButton]
&nbsp;&nbsp;&nbsp;&nbsp;
## Description 

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Arranges its children deppending of theirs minimum size and strech ratio in full rows. If theirs minimum sizes are equal then grid is formed. Each row is being left with additional free space for [ExpandableButton] to expand into, which does not mean that this space is hollow because it is splitted into sizes of all children in corresponding row. 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;See [member Control.size_flags_stretch_ratio] and [method Control.get_combined_minimum_size] for more details.
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;You might want to use [GridContainer] or <span style="color:LightGreen;"><a rel="nofollow" href="https://github.com/Magodra/SpanningTableContainer">SpanningTableContainer</a></span>.
&nbsp;&nbsp;&nbsp;&nbsp;
## Tutorials 

	