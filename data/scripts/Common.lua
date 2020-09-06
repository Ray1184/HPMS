return {
    -- Key constants.
    PRESSED = 2,
    PRESSED_FIRST_TIME = 1,
    RELEASED = 3,
    NONE = 0,

    -- Actors transformations.
    loc_rot_scale = function(actor, px, py, pz, rx, ry, rz, sx, sy, sz)
        actor.position = hpms.vec3(px, py, pz)
        actor.rotation = hpms.from_euler(hpms.to_radians(rx), hpms.to_radians(ry), hpms.to_radians(rz))
        actor.scale = hpms.vec3(sx, sy, sz)
    end,
    move = function(actor, x, y, z)
        actor.position = hpms.vec3_add(actor.position, hpms.vec3(x, y, z))
    end,
    move_towards_direction = function(actor, ratio)
        local dir = hpms.get_direction(actor.rotation, hpms.vec3(0, 0, 1))
        actor.position = hpms.vec3_add(actor.position, hpms.vec3(ratio * dir.x, 0, ratio * dir.z))
    end,
    rotate = function(actor, rx, ry, rz)
        actor.rotation = hpms.quat_mul(actor.rotation, hpms.from_euler(hpms.to_radians(rx), hpms.to_radians(ry), hpms.to_radians(rz)))
    end
}