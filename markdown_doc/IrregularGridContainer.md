# IrregularGridContainer

**Inherits:** Container

\    \    Usefull [GridContainer] for [ExpandableButton]
\    
## Description 

\    \    Arranges its children deppending of theirs minimum size and strech ratio in full rows. If theirs minimum sizes are equal then grid is formed. Each row is being left with additional free space for [ExpandableButton] to expand into, which does not mean that this space is hollow because it is splitted into sizes of all children in corresponding row. 
\    \    See [member Control.size_flags_stretch_ratio] and [method Control.get_combined_minimum_size] for more details.
\    \    You might want to use [GridContainer] or <span style="color:LightGreen;"><a rel="nofollow" href="https://github.com/Magodra/SpanningTableContainer">SpanningTableContainer</a></span>.
\    
## Tutorials 

	