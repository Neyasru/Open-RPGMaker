
player = {
    GraphicsComponent = {
        imageID = "img_player";
		rows = 4;
		columns = 9;
    },
	InputComponent = {
        input = 1;
    },
    NpcComponent = {
        phrase = "Soc un player super molon"
    },
	TransformComponent = {
		x = 25;
		y = 23;
		w = 64;
		h = 64;
		scale = 1;
		speed = 0.1;
	},
}

function loadAnimations(entity)
	--args 1:Animation Name 2:RowStart 3:ColumnStart 4:NumFrames 5:Speed
	entity:setAnimation("IDLE-REAR" , 0, 0, 0, 1, 1);
	entity:setAnimation("IDLE-RIGHT", 0, 1, 0, 1, 1);
	entity:setAnimation("IDLE-FRONT", 0, 2, 0, 1, 1);
	entity:setAnimation("IDLE-LEFT" , 0, 3, 0, 1, 1);
	
	entity:setAnimation("WALKING-REAR" , 0, 0, 1, 8, 100);
	entity:setAnimation("WALKING-LEFT", 0, 1, 1, 8, 100);
	entity:setAnimation("WALKING-FRONT", 0, 2, 1, 8, 100);
	entity:setAnimation("WALKING-RIGHT" , 0, 3, 1, 8, 100);
	
end