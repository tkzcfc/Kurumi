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
                                            ["children"] = {
                                                [1] = {
                                                    ["children"] = {
                                                        [1] = {
                                                            ["type"] = "Action",
                                                            ["name"] = "Action_9",
                                                            ["func"] = "ai_run_sub_tree",
                                                            ["arg"] = {
                                                                [1] = "attack",
                                                            },
                                                        },
                                                        [2] = {
                                                            ["type"] = "Action",
                                                            ["name"] = "Action_9",
                                                            ["func"] = "ai_check_value",
                                                            ["arg"] = {
                                                                [1] = "runAttactFail",
                                                            },
                                                        },
                                                    },
                                                    ["type"] = "Sequence",
                                                    ["name"] = "Sequence_1",
                                                    ["func"] = "",
                                                    ["arg"] = {
                                                    },
                                                },
                                            },
                                            ["type"] = "Filter",
                                            ["name"] = "Filter_5",
                                            ["func"] = "ai_can_attack",
                                            ["arg"] = {
                                            },
                                        },
                                        [2] = {
                                            ["children"] = {
                                                [1] = {
                                                    ["children"] = {
                                                        [1] = {
                                                            ["type"] = "False",
                                                            ["name"] = "return true",
                                                            ["func"] = "",
                                                            ["arg"] = {
                                                            },
                                                        },
                                                    },
                                                    ["type"] = "Wait",
                                                    ["name"] = "sleep some time",
                                                    ["func"] = "",
                                                    ["arg"] = {
                                                        [1] = 0.3,
                                                        [2] = 0.5,
                                                    },
                                                },
                                                [2] = {
                                                    ["children"] = {
                                                        [1] = {
                                                            ["children"] = {
                                                                [1] = {
                                                                    ["children"] = {
                                                                        [1] = {
                                                                            ["children"] = {
                                                                                [1] = {
                                                                                    ["type"] = "Action",
                                                                                    ["name"] = "Action_4",
                                                                                    ["func"] = "ai_move_by_time",
                                                                                    ["arg"] = {
                                                                                        [1] = 0.8,
                                                                                        [2] = 2.2,
                                                                                        [3] = true,
                                                                                    },
                                                                                },
                                                                            },
                                                                            ["type"] = "Filter",
                                                                            ["name"] = "Filter_2",
                                                                            ["func"] = "ai_is_ori_left",
                                                                            ["arg"] = {
                                                                            },
                                                                        },
                                                                        [2] = {
                                                                            ["type"] = "Action",
                                                                            ["name"] = "Action_4",
                                                                            ["func"] = "ai_move_by_time",
                                                                            ["arg"] = {
                                                                                [1] = 0.8,
                                                                                [2] = 2.2,
                                                                                [3] = false,
                                                                            },
                                                                        },
                                                                    },
                                                                    ["type"] = "Selector",
                                                                    ["name"] = "Selector_4",
                                                                    ["func"] = "",
                                                                    ["arg"] = {
                                                                    },
                                                                },
                                                            },
                                                            ["type"] = "Filter",
                                                            ["name"] = "Filter_3",
                                                            ["func"] = "ai_is_dis_too_long",
                                                            ["arg"] = {
                                                                [1] = 1000,
                                                            },
                                                        },
                                                        [2] = {
                                                            ["children"] = {
                                                                [1] = {
                                                                    ["children"] = {
                                                                        [1] = {
                                                                            ["children"] = {
                                                                                [1] = {
                                                                                    ["children"] = {
                                                                                        [1] = {
                                                                                            ["type"] = "Action",
                                                                                            ["name"] = "Action_4",
                                                                                            ["func"] = "ai_move_by_time",
                                                                                            ["arg"] = {
                                                                                                [1] = 0.8,
                                                                                                [2] = 2.2,
                                                                                                [3] = true,
                                                                                            },
                                                                                        },
                                                                                        [2] = {
                                                                                            ["type"] = "Action",
                                                                                            ["name"] = "Action_4",
                                                                                            ["func"] = "ai_move_by_time",
                                                                                            ["arg"] = {
                                                                                                [1] = 0.5,
                                                                                                [2] = 1.5,
                                                                                                [3] = false,
                                                                                            },
                                                                                        },
                                                                                    },
                                                                                    ["type"] = "RandomSelector",
                                                                                    ["name"] = "RandomSelector_3",
                                                                                    ["func"] = "",
                                                                                    ["arg"] = {
                                                                                        [1] = 3,
                                                                                        [2] = 1,
                                                                                    },
                                                                                },
                                                                            },
                                                                            ["type"] = "Filter",
                                                                            ["name"] = "Filter_2",
                                                                            ["func"] = "ai_is_ori_left",
                                                                            ["arg"] = {
                                                                            },
                                                                        },
                                                                        [2] = {
                                                                            ["children"] = {
                                                                                [1] = {
                                                                                    ["type"] = "Action",
                                                                                    ["name"] = "Action_4",
                                                                                    ["func"] = "ai_move_by_time",
                                                                                    ["arg"] = {
                                                                                        [1] = 0.5,
                                                                                        [2] = 1.5,
                                                                                        [3] = true,
                                                                                    },
                                                                                },
                                                                                [2] = {
                                                                                    ["type"] = "Action",
                                                                                    ["name"] = "Action_4",
                                                                                    ["func"] = "ai_move_by_time",
                                                                                    ["arg"] = {
                                                                                        [1] = 0.8,
                                                                                        [2] = 2.2,
                                                                                        [3] = false,
                                                                                    },
                                                                                },
                                                                            },
                                                                            ["type"] = "RandomSelector",
                                                                            ["name"] = "RandomSelector_3",
                                                                            ["func"] = "",
                                                                            ["arg"] = {
                                                                                [1] = 1,
                                                                                [2] = 3,
                                                                            },
                                                                        },
                                                                    },
                                                                    ["type"] = "Selector",
                                                                    ["name"] = "Selector_4",
                                                                    ["func"] = "",
                                                                    ["arg"] = {
                                                                    },
                                                                },
                                                                [2] = {
                                                                    ["type"] = "Action",
                                                                    ["name"] = "shun yi",
                                                                    ["func"] = "ai_do_skill5",
                                                                    ["arg"] = {
                                                                    },
                                                                },
                                                            },
                                                            ["type"] = "RandomSelector",
                                                            ["name"] = "RandomSelector_3",
                                                            ["func"] = "",
                                                            ["arg"] = {
                                                                [1] = 4,
                                                                [2] = 1,
                                                            },
                                                        },
                                                    },
                                                    ["type"] = "Selector",
                                                    ["name"] = "Selector_5",
                                                    ["func"] = "",
                                                    ["arg"] = {
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
                                    },
                                },
                            },
                            ["type"] = "Filter",
                            ["name"] = "have target ????",
                            ["func"] = "ai_has_target",
                            ["arg"] = {
                            },
                        },
                        [2] = {
                            ["children"] = {
                                [1] = {
                                    ["type"] = "Action",
                                    ["name"] = "Action_2",
                                    ["func"] = "ai_find_target",
                                    ["arg"] = {
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
                            },
                        },
                    },
                    ["type"] = "Selector",
                    ["name"] = "have target ????",
                    ["func"] = "",
                    ["arg"] = {
                    },
                },
            },
            ["type"] = "Start",
            ["name"] = "",
            ["arg"] = {
            },
        },
    },
}