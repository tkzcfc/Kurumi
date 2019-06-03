return {
    ["title"] = "new Tree",
    ["nodes"] = {
        [1] = {
            ["func"] = "",
            ["children"] = {
                [1] = {
                    ["children"] = {
                        [1] = {
                            ["children"] = {
                                [1] = {
                                    ["children"] = {
                                        [1] = {
                                            ["type"] = "Condition",
                                            ["name"] = "ai_can_attack",
                                            ["func"] = "ai_do_attack_tree",
                                            ["arg"] = {
                                                [1] = "",
                                            },
                                        },
                                        [2] = {
                                            ["children"] = {
                                                [1] = {
                                                    ["children"] = {
                                                        [1] = {
                                                            ["type"] = "True",
                                                            ["name"] = "return true",
                                                            ["func"] = "",
                                                            ["arg"] = {
                                                                [1] = "",
                                                            },
                                                        },
                                                    },
                                                    ["type"] = "Wait",
                                                    ["name"] = "sleep some time",
                                                    ["func"] = "",
                                                    ["arg"] = {
                                                        [1] = 0.3,
                                                        [2] = 1,
                                                    },
                                                },
                                                [2] = {
                                                    ["type"] = "Action",
                                                    ["name"] = "Action_3",
                                                    ["func"] = "ai_move_by_time",
                                                    ["arg"] = {
                                                        [1] = 0.5,
                                                        [2] = 1.5,
                                                    },
                                                },
                                            },
                                            ["type"] = "RandomSelector",
                                            ["name"] = "Wandering",
                                            ["func"] = "",
                                            ["arg"] = {
                                                [1] = 2,
                                                [2] = 1,
                                            },
                                        },
                                    },
                                    ["type"] = "Selector",
                                    ["name"] = "",
                                    ["func"] = "",
                                    ["arg"] = {
                                        [1] = "",
                                    },
                                },
                            },
                            ["type"] = "Filter",
                            ["name"] = "have target ????",
                            ["func"] = "ai_has_target",
                            ["arg"] = {
                                [1] = "",
                            },
                        },
                        [2] = {
                            ["children"] = {
                                [1] = {
                                    ["type"] = "Action",
                                    ["name"] = "Action_2",
                                    ["func"] = "ai_find_target",
                                    ["arg"] = {
                                        [1] = "",
                                    },
                                },
                                [2] = {
                                    ["children"] = {
                                        [1] = {
                                            ["children"] = {
                                                [1] = {
                                                    ["type"] = "True",
                                                    ["name"] = "return true",
                                                    ["func"] = "",
                                                    ["arg"] = {
                                                        [1] = "",
                                                    },
                                                },
                                            },
                                            ["type"] = "Wait",
                                            ["name"] = "sleep some time",
                                            ["func"] = "",
                                            ["arg"] = {
                                                [1] = 1,
                                                [2] = 5,
                                            },
                                        },
                                        [2] = {
                                            ["type"] = "Action",
                                            ["name"] = "Action_3",
                                            ["func"] = "ai_move_by_time",
                                            ["arg"] = {
                                                [1] = 0.5,
                                                [2] = 1.5,
                                            },
                                        },
                                    },
                                    ["type"] = "RandomSelector",
                                    ["name"] = "Wandering",
                                    ["func"] = "",
                                    ["arg"] = {
                                        [1] = 3,
                                        [2] = 1,
                                    },
                                },
                            },
                            ["type"] = "Selector",
                            ["name"] = "no target",
                            ["func"] = "",
                            ["arg"] = {
                                [1] = "",
                            },
                        },
                    },
                    ["type"] = "Selector",
                    ["name"] = "have target ????",
                    ["func"] = "",
                    ["arg"] = {
                        [1] = "",
                    },
                },
            },
            ["type"] = "Start",
            ["name"] = "",
            ["arg"] = {
                [1] = "",
            },
        },
    },
}