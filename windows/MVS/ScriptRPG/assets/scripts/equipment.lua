equipments = {
	plate_hands = 0;
	plate_head = 1;
	plate_legs = 2;
	plate_armor = 3;
	plate_feets = 4;
}

plate_hands = {
	GraphicsComponent = {
		imageID = "img_hand_plate";
		rows = 4;
		columns = 9;
	},
	TransformComponent = {
		x = 0;
		y = 0;
		w = 64;
		h = 64;
		scale = 1;
	},
}

plate_head = {
	GraphicsComponent = {
		imageID = "img_head_plate";
		rows = 4;
		columns = 9;
	},
	TransformComponent = {
		x = 0;
		y = 0;
		w = 64;
		h = 64;
		scale = 1;
		speed = 0.1;
	},
	
}

plate_legs = {
	GraphicsComponent = {
		imageID = "img_legs_plate";
		rows = 4;
		columns = 9;
	},
	TransformComponent = {
		x = 0;
		y = 0;
		w = 64;
		h = 64;
		scale = 1;
		speed = 0.1;
	},
}

plate_armor = {
	GraphicsComponent = {
		imageID = "img_torso_plate";
		rows = 4;
		columns = 9;
	},
	TransformComponent = {
		x = 0;
		y = 0;
		w = 64;
		h = 64;
		scale = 1;
		speed = 0.1;
	},
}
plate_feets = {
	GraphicsComponent = {
		imageID = "img_feet_plate";
		rows = 4;
		columns = 9;
	},
	TransformComponent = {
		x = 0;
		y = 0;
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