# RevisedButton

**Inherits:** BaseButton
  
[Button] wich uses [RichTextLable] to show text.  

## Description 
  
[RevisedButton] is more complex themed button than [Button]. It can contain text and an icon, and it will display them according to the current [Theme].  
**Example of creating a [RevisedButton] and assigning an action when pressed by code:**  
  
```gdscript
  
		func _ready() -> void:  
		    var button = RevisedButton.new()  
		    button.text = "[i]Click[/i] [b][color=LightGreen]me[/color][/b]"  
		    button.pressed.connect(self._revised_button_pressed)  
		    add_child(button)  
		    button.size = Vector2(125,45)  
  
		func _revised_button_pressed():  
		    print_rich("[color=Violet]Hello world![/color]")  
		  
```  
```csharp
  
		public override void _Ready()  
		{  
		    var button = new RevisedButton();  
		    button.Text = "[i]Click[/i] [b][color=LightGreen]me[/color][/b]";  
		    button.Size.X = 125;  
		    button.Size.Y = 45;  
		    button.Pressed += RevisedButtonPressed;  
		    AddChild(button);  
		}  
  
		private void RevisedButtonPressed()  
		{  
		    GD.Print("Hello world!");  
		}  
		  
```  
  
See also [BaseButton] which contains common properties and methods associated with this node.  
**Note:** Buttons do not interpret touch input and therefore don't support multitouch, since mouse emulation can only press one button at a given time. Use [TouchScreenButton] for buttons that trigger gameplay movement or actions.  

## Tutorials 

	