# AnimatedTabContainer

**Inherits:** Container

\    \    An animated container that connects each child control as a retractable tab whit [AnimatedBar] children.
\    
## Description 

\    \    Resizes and sets position of all [AnimatedBar] children so they appear on sides(default bottom and right). Cosiders rest of the controll children as tabs. Initially all tabs are hidden but when one of bars' button is pressed current tab is changed and extended or retracted.
\    \    **Examples of tabs ordering:[br]1.  **If it has one bar child with 5 buttons and 3 other controll childs then pressing bar's first button will show up the first controll child, the second will show up the second and the third the third. However, pressing bar's fourth or fifth button will only hide curently shown tab and do nothing when none is curently shown.[br]**2.  **If it has two [AnimatedBar] children first with two buttons, second with 3 and 6 other controll children then pressing buttons of first bar whil work the same way as in example above but pressing buttons of second bar will open tab by two higher(eg. second button will open fourth tab) because first two tabs are reserved for first bar as it has two buttons.
\    \    See also [TabContainer] for inanimate tab container.
\    
## Tutorials 

	