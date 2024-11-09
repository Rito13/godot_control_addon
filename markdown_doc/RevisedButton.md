# RevisedButton

**Inherits:** BaseButton
  
[Button] wich uses [RichTextLable] to show text.  

## Description 
  
[RevisedButton] is more complex themed button than [Button]. It can contain text and an icon, and it will display them according to the current [Theme].  
**Example of creating a [RevisedButton] and assigning an action when pressed by code:**  
```csharp
  
		[gdscript]  
		func _ready() -&gt; void:  
		    var button = RevisedButton.new()  
		    button.text = &quot;[i]Click[/i] [b][color=LightGreen]me[/color][/b]&quot;  
		    button.pressed.connect(self._revised_button_pressed)  
		    add_child(button)  
		    button.size = Vector2(125,45)  
  
		func _revised_button_pressed():  
		    print_rich(&quot;[color=Violet]Hello world![/color]&quot;)  
		[/gdscript]  
		[csharp]  
		public override void _Ready()  
		{  
		    var button = new RevisedButton();  
		    button.Text = &quot;[i]Click[/i] [b][color=LightGreen]me[/color][/b]&quot;;  
		    button.Size.X = 125;  
		    button.Size.Y = 45;  
		    button.Pressed += RevisedButtonPressed;  
		    AddChild(button);  
		}  
  
		private void RevisedButtonPressed()  
		{  
		    GD.Print(&quot;Hello world!&quot;);  
		}  
		[/csharp]  
		  
```  
See also [BaseButton] which contains common properties and methods associated with this node.  
**Note:** Buttons do not interpret touch input and therefore don't support multitouch, since mouse emulation can only press one button at a given time. Use [TouchScreenButton] for buttons that trigger gameplay movement or actions.  

## Tutorials 

	